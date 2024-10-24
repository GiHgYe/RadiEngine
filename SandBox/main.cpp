#include <iostream>
#include <glad.h>
#include <glfw3.h>

#include "engine.h"
#include "login_scene.h"
#include "renderer/texture2d.h"
#include "renderer/mesh_filter.h"
#include "renderer/shader.h"
#include "renderer/material.h"
#include "renderer/mesh_renderer.h"
#include "renderer/camera.h"
#include "component/component.h"
#include "component/game_object.h"
#include "component/transform.h"
#include "control/key_code.h"
#include "control/input.h"
#include <reflection/all_reflection.h>

#pragma comment(lib, "yaml-cpp.lib")

GLFWwindow* window;

void init_opengl()
{
    glfwSetErrorCallback([](int error, const char* description) { fprintf(stderr, "GLFW Error %d: %s\n", error, description); });

    if (!glfwInit())
        throw std::runtime_error("Failed to init GLFW window");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(960, 640, "SandBox", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    glfwSwapInterval(1);
    glViewport(0, 0, 960, 640);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* windowint, int width, int height) { glViewport(0, 0, width, height); });
}

using namespace std;

int main()
{
    init_opengl();
    Reflection::TypeMetaRegister::metaRegister();

    Engine::InitOpengl();
    GameObject* login_scene = new GameObject("Login Scene Go");
    login_scene->AddComponent(LoginScene);
    login_scene->AddComponent(Transform);

    Engine::Run();

    glfwDestroyWindow(window);
    glfwTerminate();
    Reflection::TypeMetaRegister::metaUnregister();
    return 0;
}