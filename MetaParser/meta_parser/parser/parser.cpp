#include "parser.h"
#include "../types/class.h"
#include "../types/method.h"
#include "../generator/reflection_generator.h"
#include "../generator/serializer_generator.h"
#pragma comment(lib, "libclang.lib")

#include <filesystem>
#include <iostream>

MetaParser::MetaParser(const std::string project_path,
	const std::string include_file_path,
	const std::string include_path,
	const std::string sys_include,
	bool              is_show_errors) 
	: m_project_input_path(project_path),
	m_source_include_file_name(include_file_path), m_index(nullptr), m_translate_unit(nullptr),
	m_sys_include(sys_include), m_is_show_error(is_show_errors)
{
	m_work_paths = Utils::split(include_path, ";");

	m_generators.emplace_back(new SerializerGenerator(m_work_paths[0], std::bind(&MetaParser::getIncludeFile, this, std::placeholders::_1)));
	m_generators.emplace_back(new ReflectionGenerator(m_work_paths[0], std::bind(&MetaParser::getIncludeFile, this, std::placeholders::_1)));
}

MetaParser::~MetaParser()
{
	for (auto& generator : m_generators)	delete generator;
	if (m_translate_unit)					clang_disposeTranslationUnit(m_translate_unit);
	if (m_index)							clang_disposeIndex(m_index);
}

void MetaParser::Finish(void)
{
	for (auto& generator : m_generators)
		generator->Finish();
}

void MetaParser::GetProjectIncludes(const std::string& project_path, std::vector<std::string>& include_files)
{
	for (auto& it : std::filesystem::directory_iterator(project_path))
	{
		if (it.path().filename() == "Dependencies" || it.path().filename() == "MetaParser" ||
			it.path().filename() == "MetaGenerate" || it.path().filename() == "Test") continue;
		if (it.is_directory()) {
			GetProjectIncludes(it.path().string(), include_files);
		}
		else if (it.is_regular_file()) {
			if (it.path().extension() == ".h") {
				include_files.push_back(it.path().string());
			}
		}
	}
}

bool MetaParser::parseProject(void) 
{
	std::cout << "Parsing project file: " << m_project_input_path << std::endl;

	std::vector<std::string> inlcude_files;
	GetProjectIncludes(m_project_input_path, inlcude_files);

	std::fstream include_file;

	include_file.open(m_source_include_file_name, std::ios::out);
	if (!include_file.is_open())
	{
		std::cout << "Could not open the Source Include file: " << m_source_include_file_name << std::endl;
		return false;
	}

	std::cout << "Generating the Source Include file: " << m_source_include_file_name << std::endl;

	std::string output_filename = Utils::getFileName(m_source_include_file_name);

	if (output_filename.empty())
	{
		output_filename = "META_INPUT_HEADER_H";
	}
	else
	{
		Utils::replace(output_filename, ".", "_");
		Utils::replace(output_filename, " ", "_");
		Utils::toUpper(output_filename);
	}
	include_file << "#ifndef __" << output_filename << "__" << std::endl;
	include_file << "#define __" << output_filename << "__" << std::endl;

	for (auto include_item : inlcude_files)
	{
		std::string temp_string(include_item);
		Utils::replace(temp_string, '\\', '/');
		include_file << "#include  \"" << temp_string << "\"" << std::endl;
	}

	include_file << "#endif" << std::endl;
	include_file.close();
	return true;
}

int MetaParser::Parse(void)
{
	if (!parseProject()) return -1;

	std::cerr << "Parsing the whole project..." << std::endl;
	m_index = clang_createIndex(1, m_is_show_error ? 1 : 0);
	std::string pre_include = "-I";
	std::string sys_include_temp;

	if (!(m_sys_include == "*"))
	{
		sys_include_temp = pre_include + m_sys_include;
		cmd.emplace_back(sys_include_temp.c_str());
	}

	auto paths = m_work_paths;
	for (int index = 0; index < paths.size(); ++index)
	{
		paths[index] = pre_include + paths[index];
		cmd.emplace_back(paths[index].c_str());
	}

	std::filesystem::path input_path(m_source_include_file_name);
	if (!std::filesystem::exists(input_path)) {
		std::cerr << input_path << " is not exist" << std::endl;
		return -2;
	}

	m_translate_unit = clang_createTranslationUnitFromSourceFile( m_index, m_source_include_file_name.c_str()
																  , static_cast<int>(cmd.size()), cmd.data(), 0, nullptr);
	Cursor cursor = clang_getTranslationUnitCursor(m_translate_unit);

	Namespace tmp_namespace;

	BuildClassAST(cursor, tmp_namespace);

	tmp_namespace.clear();

	return 0;
}

void MetaParser::BuildClassAST(const Cursor& cursor, Namespace& current_namespace) 
{
	for (auto& child : cursor.GetChildren()) 
	{
		CXCursorKind kind = child.GetKind();

		if (child.isDefinition() && (kind == CXCursor_ClassDecl || kind == CXCursor_StructDecl) ) 
		{
			auto class_ptr = std::make_shared<Class>(child, current_namespace);
			if (class_ptr->ShouldCompile())
			{ 
				auto file = class_ptr->GetSourceFile();
				m_schema_modules[file].classes.emplace_back(class_ptr); 
				m_type_table[class_ptr->m_display_name] = file;
			}
		}
		else 
		{
			if (kind == CXCursor_Namespace) 
			{
				auto display_name = child.GetDisplayName();
				if (!display_name.empty())
				{
					current_namespace.emplace_back(display_name);
					BuildClassAST(child, current_namespace);
					current_namespace.pop_back();
				} 
			}
		}
	}
}

void MetaParser::GenerateFiles(void)
{
	std::cerr << "Start generate runtime schemas(" << m_schema_modules.size() << ")..." << std::endl;
	for (auto& schema : m_schema_modules)
	{
		for (auto& generator_iter : m_generators)
		{
			generator_iter->Generate(schema.first, schema.second);
		}
	}
	Finish();
}

std::string MetaParser::getIncludeFile(std::string name) { 
	auto it = m_type_table.find(name);
	return it == m_type_table.end() ? std::string() : it->second;
}