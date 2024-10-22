#include "reflection_generator.h"
#include "../template/template_manager.hpp"
#include "../types/class.h"
#include <map>

ReflectionGenerator::ReflectionGenerator(std::string source_directory, std::function<std::string(std::string)> get_include_function)
	: GeneratorInterface(source_directory + "/reflection", source_directory, get_include_function)
{
	PrepareStatus(m_out_path);
}

void ReflectionGenerator::PrepareStatus(std::string path)
{
	GeneratorInterface::PrepareStatus(path);
	TemplateManager::GetInstance()->LoadTemplates(m_root_path, "commonReflectionFile");
	TemplateManager::GetInstance()->LoadTemplates(m_root_path, "allReflectionFile");
}

std::string ReflectionGenerator::ProcessFileName(std::string path)
{
	auto relativeDir = std::filesystem::path(path).filename().replace_extension("reflection.gen.h").string();
	return m_out_path + "/" + relativeDir;
}

void ReflectionGenerator::Generate(std::string path, SchemaMoudle schema)
{
	std::string file_path = ProcessFileName(path);

	Mustache::data mustache_data;
	Mustache::data include_headfiles{ Mustache::data::type::list };
	Mustache::data class_defines{ Mustache::data::type::list };

	include_headfiles.push_back(Mustache::data{ "headfile_name", Utils::makeRelativePath(m_root_path, path).string() });

	std::map<std::string, bool> class_name;

	for (auto& class_temp : schema.classes) 
	{
		if (!class_temp->ShouldCompile()) continue;

		class_name.insert_or_assign(class_temp->GetClassName(), true);

		std::vector<std::string> field_names;
		std::map<std::string, std::pair<std::string, std::string>> vector_map;

		Mustache::data class_def;
		Mustache::data vector_defines(Mustache::data::type::list);

		GenClassRenderData(class_temp, class_def);
		for (auto& field : class_temp->m_fields)
		{
			if (!field->ShouldCompile()) continue;

			field_names.emplace_back(field->m_name);
			bool is_array = field->m_type.find("std::vector<") == 0;
			if (is_array)
			{
				std::string array_useful_name = field->m_type;

				Utils::formatQualifiedName(array_useful_name);

				std::string item_type = field->m_type;

				item_type = Utils::getNameWithoutContainer(item_type);

				vector_map[field->m_type] = std::make_pair(array_useful_name, item_type);
			}
		}

		if (vector_map.size() > 0) {
			if (nullptr == class_def.get("vector_exist"))
				class_def.set("vector_exist", true);

			for (auto& vector_item : vector_map) 
			{
				std::string array_useful_name	= vector_item.second.first;
				std::string item_type			= vector_item.second.second;
				Mustache::data vector_define;
				vector_define.set("vector_useful_name", array_useful_name);
				vector_define.set("vector_type_name", vector_item.first);
				vector_define.set("vector_element_type_name", item_type);
				vector_defines.push_back(vector_define);
			}
		}
		class_def.set("vector_defines", vector_defines);
		class_defines.push_back(class_def);
	}

	mustache_data.set("class_defines", class_defines);
	mustache_data.set("include_headfiles", include_headfiles);

	std::string tmp = Utils::convertNameToUpperCamelCase(std::filesystem::path(path).stem().string(), "_");
	mustache_data.set("sourefile_name_upper_camel_case", tmp);

	std::string render_string = TemplateManager::GetInstance()->RenderByTemplate("commonReflectionFile", mustache_data);
	Utils::saveFile(render_string, file_path);

	m_sourcefile_list.emplace_back(tmp);
	m_head_file_list.emplace_back(Utils::makeRelativePath(m_root_path, file_path).string());

}

void ReflectionGenerator::Finish()
{
	Mustache::data mustache_data;
	Mustache::data include_headfiles = Mustache::data::type::list;
	Mustache::data sourefile_names = Mustache::data::type::list;

	for (auto& head_file : m_head_file_list)
	{
		include_headfiles.push_back(Mustache::data("headfile_name", head_file));
	}
	for (auto& sourefile_name_upper_camel_case : m_sourcefile_list)
	{
		sourefile_names.push_back(Mustache::data("sourefile_name_upper_camel_case", sourefile_name_upper_camel_case));
	}

	mustache_data.set("include_headfiles", include_headfiles);
	mustache_data.set("sourefile_names", sourefile_names);

	std::string render_string = TemplateManager::GetInstance()->RenderByTemplate("allReflectionFile", mustache_data);
	Utils::saveFile(render_string, m_out_path + "/all_reflection.h");
}