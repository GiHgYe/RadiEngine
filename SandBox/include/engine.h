#pragma once
#include <string>
#include <glad.h>
#include <glfw3.h>

class Engine
{
public:
    static const std::string& data_path() { return data_path_; }
    static void set_data_path(std::string data_path) { data_path_ = data_path; }

    /// 初始化OpenGL
    static void InitOpengl();

    static void Run();

    static void UpdateScreenSize();

    /// 每一帧内逻辑代码。
    static void LogicTick();

    /// 逻辑代码执行后，应用到渲染。
    static void RenderTick();

private:
    static std::string data_path_;

    static GLFWwindow* glfw_window_;
};