#pragma once
#include "generator.h"

class ReflectionGenerator :  public GeneratorInterface
{
public:
	ReflectionGenerator() = delete;
	ReflectionGenerator(std::string source_directory, std::function<std::string(std::string)> get_include_function);
	~ReflectionGenerator() override {}

	virtual void Generate(std::string path, SchemaMoudle schema) override;
	virtual void Finish() override;

protected:
	virtual void        PrepareStatus(std::string path) override;
	virtual std::string ProcessFileName(std::string path) override;

private:
	std::vector<std::string> m_head_file_list;
	std::vector<std::string> m_sourcefile_list;
};

