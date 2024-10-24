#pragma once
#include <string>
#include <glad.h>
#include <glfw3.h>

class Engine
{
public:
    static const std::string& data_path() { return data_path_; }
    static void set_data_path(std::string data_path) { data_path_ = data_path; }

    /// ��ʼ��OpenGL
    static void InitOpengl();

    static void Run();

    static void UpdateScreenSize();

    /// ÿһ֡���߼����롣
    static void LogicTick();

    /// �߼�����ִ�к�Ӧ�õ���Ⱦ��
    static void RenderTick();

private:
    static std::string data_path_;

    static GLFWwindow* glfw_window_;
};