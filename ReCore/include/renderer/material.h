#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <math/math_headers.h>
#include "component/component.h"

class Shader;
class Texture2D;

class Material
{
public:
	Material();
	~Material();

	void Parse(const std::string& material_path);//加载Material文件并解析

    Shader* shader() { return shader_; }

    void SetUniform1i(const std::string& shader_property_name, int value);
    void SetUniform1f(const std::string& shader_property_name, float value);
    void SetUniform3f(const std::string& shader_property_name, Vector3& value);
    void SetUniformMatrix4f(const std::string& shader_property_name, Matrix4x4& value);

    void SetTexture(const std::string& property, Texture2D* texture2D);

    std::vector<std::pair<std::string, Texture2D*>>& textures() { return textures_; }
    std::unordered_map<std::string, int>& uniform_1i_map() { return uniform_1i_map_; }
    std::unordered_map<std::string, float>& uniform_1f_map() { return uniform_1f_map_; }
    std::unordered_map<std::string, Vector3>& uniform_3f_map() { return uniform_3f_map_; }
    std::unordered_map<std::string, Matrix4x4>& uniform_matrix4f_map() { return uniform_matrix4f_map_; }

private:
    Shader* shader_{};
    std::vector<std::pair<std::string, Texture2D*>> textures_;

    std::unordered_map<std::string, int> uniform_1i_map_;
    std::unordered_map<std::string, float> uniform_1f_map_;
    std::unordered_map<std::string, Vector3> uniform_3f_map_;
    std::unordered_map<std::string, Matrix4x4> uniform_matrix4f_map_;
};