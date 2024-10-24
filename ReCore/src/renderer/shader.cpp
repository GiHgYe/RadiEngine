#include "renderer/shader.h"
#include "utils/debug.h"
#include <iostream>
#include <fstream>
#include <glad.h>


std::unordered_map<std::string, Shader*> Shader::kShaderMap;

Shader::Shader() = default;

Shader::~Shader() = default;

Shader* Shader::Find(std::string shader_name) {
    std::unordered_map<std::string, Shader*>::iterator iter = kShaderMap.find(shader_name);
    if (iter != kShaderMap.end()) {
        return iter->second;
    }

    Shader* shader = new Shader();
    shader->Parse(shader_name);

    kShaderMap.insert(std::pair<std::string, Shader*>(shader_name, shader));

    return shader;
}

void Shader::Parse(std::string shader_name) {
    shader_name_ = shader_name;

    // 组装完整文件路径
    std::string vertex_shader_file_path = shader_name + ".vert";
    std::string fragment_shader_file_path = shader_name + ".frag";

    // 读取顶点Shader代码
    std::ifstream vertex_shader_input_file_stream(vertex_shader_file_path);
    std::string vertex_shader_source((std::istreambuf_iterator<char>(vertex_shader_input_file_stream)), std::istreambuf_iterator<char>());
    // 读取片段Shader代码
    std::ifstream fragment_shader_input_file_stream(fragment_shader_file_path);
    std::string fragment_shader_source((std::istreambuf_iterator<char>(fragment_shader_input_file_stream)), std::istreambuf_iterator<char>());

    CreateShaderProgram(vertex_shader_source.c_str(), fragment_shader_source.c_str());
    //ConnectUniformBlockAndBindingPoint();
}

void Shader::CreateShaderProgram(const char* vertex_shader_text, const char* fragment_shader_text) {
    //创建顶点Shader
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    //指定Shader源码
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    //编译Shader
    glCompileShader(vertex_shader);
    //获取编译结果
    GLint compile_status = GL_FALSE;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        GLchar message[256];
        glGetShaderInfoLog(vertex_shader, sizeof(message), 0, message);
        LOG_ERROR("compile vertex shader error:{}", message);
    }

    //创建片段Shader
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    //指定Shader源码
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    //编译Shader
    glCompileShader(fragment_shader);
    //获取编译结果
    compile_status = GL_FALSE;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        GLchar message[256];
        glGetShaderInfoLog(fragment_shader, sizeof(message), 0, message);
        LOG_ERROR("compile fragment shader error:{}", message);
    }

    //创建GPU程序
    shader_program_handle_ = glCreateProgram();
    //附加Shader
    glAttachShader(shader_program_handle_, vertex_shader);
    glAttachShader(shader_program_handle_, fragment_shader);
    //Link
    glLinkProgram(shader_program_handle_);
    //获取编译结果
    GLint link_status = GL_FALSE;
    glGetProgramiv(shader_program_handle_, GL_LINK_STATUS, &link_status);
    if (link_status == GL_FALSE)
    {
        GLchar message[256];
        glGetProgramInfoLog(shader_program_handle_, sizeof(message), 0, message);
        LOG_ERROR("link shader error:{}", message);
    }
}

void Shader::Active() {
    glUseProgram(shader_program_handle_);
}

void Shader::InActive() {

}
