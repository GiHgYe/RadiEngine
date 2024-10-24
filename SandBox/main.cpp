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

using namespace std;

int main()
{
    Reflection::TypeMetaRegister::metaRegister();

    Engine::InitOpengl();
    GameObject* login_scene = new GameObject("Login Scene Go");
    login_scene->AddComponent(LoginScene);
    login_scene->AddComponent(Transform);

    Engine::Run();

    Reflection::TypeMetaRegister::metaUnregister();
    return 0;
}