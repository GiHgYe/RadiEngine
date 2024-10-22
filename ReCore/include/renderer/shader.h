#pragma once

#include <string>
#include <unordered_map>
#include <map>


class Shader
{
public:
	Shader();
	~Shader();

public:
	void Parse(std::string shader_name);//加载Shader文件并解析
	void CreateShaderProgram(const char* vertex_shader_text, const char* fragment_shader_text);

	//void ConnectUniformBlockAndBindingPoint();

	//void Active();//激活
	//void InActive();//禁用

	unsigned int shader_program_handle() const { return shader_program_handle_; }//Shader程序句柄;

public:
	static Shader* Find(std::string shader_name);

private:
	static std::unordered_map<std::string, Shader*> kShaderMap;

private:
	std::string shader_name_;
	unsigned int shader_program_handle_;
	//std::unordered_map<std::string, unsigned int> uniform_block_binding_point_map;
};

