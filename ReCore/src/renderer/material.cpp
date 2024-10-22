#include "renderer/material.h"
#include <iostream>
#include "renderer/shader.h"
#include "renderer/texture2d.h"
#include <yaml-cpp/yaml.h>

Material::Material() = default;

Material::~Material() = default;

void Material::Parse(const std::string& material_path) {

    YAML::Node document;
    try
    {
        document = YAML::LoadFile(material_path);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return;
    }

    //根节点
    YAML::Node material_node = document["material"];
    if (!material_node.IsMap()) 
        return;

    YAML::Node material_shader_attribute = material_node["shader"];
    if (!material_shader_attribute.IsScalar()) {
        return;
    }
    shader_ = Shader::Find(material_shader_attribute.Scalar());

    //解析Texture
    YAML::Node material_texture_node = material_node["texture"];
    if (!material_texture_node.IsSequence()) {
        return;
    }
    for (auto it = material_texture_node.begin(); it != material_texture_node.end(); it++)
    {
        YAML::Node texture_name_attribute = (*it)["name"];
        if (!texture_name_attribute.IsScalar()) {
            return;
        }

        YAML::Node texture_image_attribute = (*it)["image"];
        if (!texture_image_attribute.IsScalar()) {
            return;
        }

        std::string shader_property_name = texture_name_attribute.Scalar();
        std::string image_path = texture_image_attribute.Scalar();
        textures_.emplace_back(shader_property_name, image_path.empty() ? nullptr : Texture2D::LoadFromFile(image_path));
    }
}


void Material::SetUniform1i(const std::string& shader_property_name, int value) {
    uniform_1i_map_[shader_property_name] = value;
}

void Material::SetUniform1f(const std::string& shader_property_name, float value) {
    uniform_1f_map_[shader_property_name] = value;
}

void Material::SetUniform3f(const std::string& shader_property_name, Vector3& value) {
    uniform_3f_map_[shader_property_name] = value;
}

void Material::SetUniformMatrix4f(const std::string& shader_property_name, Matrix4x4& value) {
    uniform_matrix4f_map_[shader_property_name] = value;
}

void Material::SetTexture(const std::string& property, Texture2D* texture2D) {
    for (auto& pair : textures_) {
        if (pair.first == property) {
            if (pair.second != nullptr) {
                delete(pair.second);
                pair.second = nullptr;
            }
            pair.second = texture2D;
            break;
        }
    }
}