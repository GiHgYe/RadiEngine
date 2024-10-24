#include "engine.h"
#include <stdexcept>
#include "screen.h"
#include "control/input.h"
#include "control/key_code.h"
#include "component/component.h"
#include "component/game_object.h"
#include "component/transform.h"
#include "renderer/texture2d.h"
#include "renderer/mesh_filter.h"
#include "renderer/shader.h"
#include "renderer/material.h"
#include "renderer/mesh_renderer.h"
#include "renderer/camera.h"

std::string Engine::data_path_;
GLFWwindow* Engine::glfw_window_;


void Engine::InitOpengl()
{
    glfwSetErrorCallback([](int error, const char* description) { fprintf(stderr, "GLFW Error %d: %s\n", error, description); });

    if (!glfwInit())
        throw std::runtime_error("Failed to init GLFW window");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfw_window_ = glfwCreateWindow(960, 640, "SandBox", NULL, NULL);
    if (!glfw_window_)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(glfw_window_);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    glfwSwapInterval(1);
    glViewport(0, 0, 960, 640);
    glfwSetFramebufferSizeCallback(glfw_window_, [](GLFWwindow* windowint, int width, int height) { glViewport(0, 0, width, height); });
    glfwSetKeyCallback(glfw_window_, [](GLFWwindow* window, int key, int scancode, int action, int mods) { Input::RecordKey(key, action); });
    glfwSetMouseButtonCallback(glfw_window_, [](GLFWwindow* window, int button, int action, int mods) { Input::RecordKey(button, action); });
    glfwSetScrollCallback(glfw_window_, [](GLFWwindow* window, double x, double y) { Input::RecordScroll(y); });
    glfwSetCursorPosCallback(glfw_window_, [](GLFWwindow* window, double x, double y) { Input::set_mousePosition(x, y); });
    UpdateScreenSize();
}

void Engine::LogicTick()
{
    UpdateScreenSize();

    GameObject::Foreach([](GameObject* game_object) {
        game_object->ForeachComponent([](Component* component) {
            component->Update();
        });
    });

    Input::Update();
}

void Engine::RenderTick()
{
    Camera::Foreach([&]() {
        GameObject::Foreach([](GameObject* game_object) {
            auto mesh_renderer = game_object->GetComponent(MeshRenderer);
            if (!mesh_renderer) return;
            mesh_renderer->Render();
        });
    });
}

void Engine::Run()
{
    while (!glfwWindowShouldClose(glfw_window_)) {

        LogicTick();
        RenderTick();

        glfwSwapBuffers(glfw_window_);
        glfwPollEvents();
    }
    glfwDestroyWindow(glfw_window_);
    glfwTerminate();
}

void Engine::UpdateScreenSize()
{
    int width, height;
    glfwGetFramebufferSize(glfw_window_, &width, &height);
    glViewport(0, 0, width, height);
    Screen::set_width_height(width, height);
}
