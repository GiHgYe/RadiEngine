#pragma once

#include "../cursor/cursor.h"
#include "../common/schema_module.h"
#include "../generator/generator.h"
#include <unordered_map>

class MetaParser
{
public:
	MetaParser(const std::string project_path,
		const std::string include_file_path,
		const std::string include_path,
		const std::string sys_include,
		bool              is_show_errors);
	~MetaParser();

	void Finish(void);
	int  Parse(void);
	void GenerateFiles(void);

private:
	std::string m_project_input_path;

	std::vector<std::string> m_work_paths;
	std::string              m_sys_include;
	std::string              m_source_include_file_name;

	CXIndex m_index;
	CXTranslationUnit m_translate_unit;

	std::unordered_map<std::string, std::string> m_type_table;
	std::unordered_map<std::string, SchemaMoudle> m_schema_modules;

	std::vector<const char*> cmd = {
		"-x",
		"c++",
		"-std=c++17",
		"-D__REFLECTION_PARSER__",
		"-DNDEBUG", 
		"-D__clang__",
		"-w",
		"-MG",
		"-M",
		"-ferror-limit=0",
		"-o clangLog.txt"
	};

	std::vector<GeneratorInterface*> m_generators;

	bool m_is_show_error;

private:
	bool        parseProject(void);
	void        BuildClassAST(const Cursor& cursor, Namespace& current_namespace);
	std::string getIncludeFile(std::string name);
	static void GetProjectIncludes(const std::string& project_path, std::vector<std::string>& include_files);
};

