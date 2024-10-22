#pragma once
#include "generator.h"


class SerializerGenerator : public GeneratorInterface
{
public:
    SerializerGenerator() = delete;
    SerializerGenerator(std::string source_directory, std::function<std::string(std::string)> get_include_function);

    virtual void Generate(std::string path, SchemaMoudle schema) override;

    virtual void Finish() override;

    virtual ~SerializerGenerator() override {};

protected:
    virtual void PrepareStatus(std::string path) override;

    virtual std::string ProcessFileName(std::string path) override;

private:
    Mustache::data m_class_defines{ Mustache::data::type::list };
    Mustache::data m_include_headfiles{ Mustache::data::type::list };

};

