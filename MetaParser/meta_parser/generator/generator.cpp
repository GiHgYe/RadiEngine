#include "generator.h"
#include <filesystem>
#include "../types/class.h"

void GeneratorInterface::PrepareStatus(std::string path) 
{
	if (!std::filesystem::exists(path)) {
		std::filesystem::create_directories(path);
	}
}

void GeneratorInterface::GenClassRenderData(std::shared_ptr<Class> class_temp, Mustache::data& class_def)
{
	class_def.set("class_name", class_temp->GetClassName());
	class_def.set("class_base_class_size", std::to_string(class_temp->m_base_classes.size()));
	class_def.set("class_need_register", true);

	if (class_temp->m_base_classes.size() > 0) 
	{
		class_def.set("class_has_base", true);
		Mustache::data class_base_class_defines{ Mustache::data::type::list };
		for (int i = 0; i < class_temp->m_base_classes.size(); i++)
		{
			Mustache::data base_class_def;
			base_class_def.set("class_base_class_name", class_temp->m_base_classes[i]->name);
			base_class_def.set("class_base_class_index", std::to_string(i));
			class_base_class_defines.push_back(base_class_def);
		}
		class_def.set("class_base_class_defines", class_base_class_defines);
	}

	Mustache::data class_feild_defines{ Mustache::data::type::list };
	GenClassFieldRenderData(class_temp, class_feild_defines);
	class_def.set("class_field_defines", class_feild_defines);

	Mustache::data class_method_defines{ Mustache::data::type::list };
	GenClassMethodRenderData(class_temp, class_method_defines);
	class_def.set("class_method_defines", class_method_defines);
}

void GeneratorInterface::GenClassFieldRenderData(std::shared_ptr<Class> class_temp, Mustache::data& field_defs)
{
	for (auto& field : class_temp->m_fields)
	{
		if (!field->ShouldCompile())
			continue;
		Mustache::data field_define;
		field_define.set("class_field_name", field->m_name);
		field_define.set("class_field_type", field->m_type);
		field_define.set("class_field_display_name", field->m_display_name);
		bool is_vector = field->m_type.find("std::vector<") == 0;
		field_define.set("class_field_is_vector", is_vector);
		field_defs.push_back(field_define);
	}
}

void GeneratorInterface::GenClassMethodRenderData(std::shared_ptr<Class> class_temp, Mustache::data& method_defs)
{
	for (auto& method : class_temp->m_methods)
	{
		if (!method->ShouldCompile())
			continue;
		Mustache::data method_define;
		method_define.set("class_method_name", method->m_name);
		method_defs.push_back(method_define);
	}
}
