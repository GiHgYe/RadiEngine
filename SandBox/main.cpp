#include <iostream>
#include <glad.h>
#include <glfw3.h>

#include "application.h"
#include "renderer/texture2d.h"
#include "renderer/mesh_filter.h"
#include "renderer/shader.h"
#include "renderer/material.h"
#include "renderer/mesh_renderer.h"
#include "component/component.h"
#include "component/game_object.h"
#include "component/transform.h"
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

    GameObject* go = new GameObject("game object");

    auto transform = go->AddComponent(Transform);
    transform->m_position = { 0, 0, 0 };
    transform->m_scale = { 1, 1, 1 };
    transform->m_rotation = Quaternion::GetQuaternionFromEulerAngle({ 0, 0, 0 });


    auto mesh_filter = go->AddComponent(MeshFilter);
    static_cast<MeshFilter*>(mesh_filter)->LoadMesh("../asset/model/cube.mesh");

    auto material = go->AddComponent(Material);
    material->Parse("../asset/model/cube.mat");

    auto mesh_renderer = go->AddComponent(MeshRenderer);
    mesh_renderer->SetMaterial(material);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(49.f / 255, 77.f / 255, 121.f / 255, 1.f);

        Matrix4x4 _view = Math::MakeLookAtMatrix({0, 0, 5}, { 0, 0, 0 }, { 0, 1, 0 });
        Matrix4x4 _proj = Math::MakePerspectiveMatrix(Radian(Degree(45)), 16 / 9.0f, 0.01f, 1000.0f);

        //material->SetUniformMatrix4f("u_mvp", _mvp);

        mesh_renderer->SetView(_view);
        mesh_renderer->SetProjection(_proj);
        mesh_renderer->Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwDestroyWindow(window);
    glfwTerminate();
    Reflection::TypeMetaRegister::metaUnregister();
    return 0;
}