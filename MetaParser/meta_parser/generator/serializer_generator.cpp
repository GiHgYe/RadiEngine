#include "serializer_generator.h"
#include "../template/template_manager.hpp"
#include "../types/class.h"

SerializerGenerator::SerializerGenerator(std::string source_directory, std::function<std::string(std::string)> get_include_function)
	: GeneratorInterface(source_directory + "/serializer", source_directory, get_include_function)
{
	PrepareStatus(m_out_path);
}

void SerializerGenerator::PrepareStatus(std::string path)
{
	GeneratorInterface::PrepareStatus(path);
	TemplateManager::GetInstance()->LoadTemplates(m_root_path, "allSerializer.h");
	TemplateManager::GetInstance()->LoadTemplates(m_root_path, "allSerializer.ipp");
	TemplateManager::GetInstance()->LoadTemplates(m_root_path, "commonSerializerGenFile");
}


std::string SerializerGenerator::ProcessFileName(std::string path)
{
	auto relativeDir = std::filesystem::path(path).filename().replace_extension("serializer.gen.h").string();
	return m_out_path + "/" + relativeDir;
}

void SerializerGenerator::Generate(std::string path, SchemaMoudle schema)
{
	std::string file_path = ProcessFileName(path);

	Mustache::data muatache_data;
	Mustache::data include_headfiles(Mustache::data::type::list);
	Mustache::data class_defines(Mustache::data::type::list);

	include_headfiles.push_back(Mustache::data{ "headfile_name", Utils::makeRelativePath(m_root_path, path).string() });

	for (auto& class_temp : schema.classes) 
	{
		if (!class_temp->ShouldCompileFields()) continue;

		Mustache::data class_def;
		GenClassRenderData(class_temp, class_def);

		//class_def.set("class_name", class_temp->GetClassName());

		Mustache::data class_base_class_defines(Mustache::data::type::list);
		for (auto& base_class_temp : class_temp->m_base_classes)
		{
			auto include_file = m_get_include_func(base_class_temp->name);
			if (!include_file.empty())
			{
				auto include_file_base = ProcessFileName(include_file);
				if (file_path != include_file_base)
					include_headfiles.push_back(Mustache::data{ "headfile_name", Utils::makeRelativePath(m_root_path, include_file_base).string() });
			}
		}
		//for (auto& field : class_temp->m_fields)
		//{
		//	if (!field->ShouldCompile()) continue;
		//
		//	if (field->m_type.find("std::vector") == 0)
		//	{
		//		//std::string type_name;
		//		//auto visitor = [](CXCursor cursor, CXCursor parent, CXClientData data) {
		//		//	if (cursor.kind == CXCursor_TypeRef) {
		//		//		*(static_cast<std::string*>(data)) = Utils::toString(clang_getTypeSpelling(clang_getCursorType(cursor)));
		//		//		return CXChildVisit_Break;
		//		//	}
		//		//	return CXChildVisit_Continue;
		//		//};
		//		//field->GetCurosr().VisitChildren(visitor, &type_name);
		//		auto include_file = m_get_include_func(field->m_name);
		//		if (!include_file.empty())
		//		{
		//			auto include_file_base = ProcessFileName(include_file);
		//			if (file_path != include_file_base)
		//			{
		//				include_headfiles.push_back(Mustache::data{ "headfile_name", Utils::makeRelativePath(m_root_path, include_file_base).string() });
		//			}
		//		}
		//	}
		//}
		class_defines.push_back(class_def);
		m_class_defines.push_back(class_def);
	}

	muatache_data.set("class_defines", class_defines);
	muatache_data.set("include_headfiles", include_headfiles);
	std::string render_string = TemplateManager::GetInstance()->RenderByTemplate("commonSerializerGenFile", muatache_data);
	Utils::saveFile(render_string, file_path);

	m_include_headfiles.push_back(Mustache::data{ "headfile_name", Utils::makeRelativePath(m_root_path, file_path).string() });
}

void SerializerGenerator::Finish()
{
	Mustache::data mustache_data;
	mustache_data.set("class_defines", m_class_defines);
	mustache_data.set("include_headfiles", m_include_headfiles);

	std::string render_string = TemplateManager::GetInstance()->RenderByTemplate("allSerializer.h", mustache_data);
	Utils::saveFile(render_string, m_out_path + "/all_serializer.h");
	render_string = TemplateManager::GetInstance()->RenderByTemplate("allSerializer.ipp", mustache_data);
	Utils::saveFile(render_string, m_out_path + "/all_serializer.ipp");
}
