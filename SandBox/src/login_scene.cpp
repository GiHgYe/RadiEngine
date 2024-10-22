#include "login_scene.h"
#include "control/key_code.h"
#include "component/game_object.h"
#include "component/transform.h"
#include "renderer/texture2d.h"
#include "renderer/mesh_filter.h"
#include "renderer/shader.h"
#include "renderer/material.h"
#include "renderer/mesh_renderer.h"
#include "renderer/camera.h"
#include <math/math_headers.h>

LoginScene::LoginScene() :Component()
{

}

void LoginScene::Awake() {
    //创建模型 GameObject
    GameObject* go = new GameObject("cube");
    go->set_layer(0x01);

    //挂上 Transform 组件
    transform_cube_ = go->AddComponent(Transform);

    //挂上 MeshFilter 组件
    auto mesh_filter = go->AddComponent(MeshFilter);
    mesh_filter->LoadMesh("../asset/model/cube.mesh");

    //挂上 MeshRenderer 组件
    auto mesh_renderer = go->AddComponent(MeshRenderer);
    Material* material = new Material();//设置材质
    material->Parse("../asset/model/cube.mat");
    mesh_renderer->SetMaterial(material);

    //创建相机2 GameObject
    auto go_camera_2 = new GameObject("main_camera");
    //挂上 Transform 组件
    transform_camera_2_ = go_camera_2->AddComponent(Transform);
    transform_camera_2_->m_position = { 1.5, 0, 5 };
    //挂上 Camera 组件
    camera_2_ = go_camera_2->AddComponent(Camera);
    camera_2_->set_clear_flag(GL_DEPTH_BUFFER_BIT);
    camera_2_->set_depth(1);
    camera_2_->set_culling_mask(0x02);


    //创建相机1 GameObject
    auto go_camera_1 = new GameObject("main_camera");
    //挂上 Transform 组件
    transform_camera_1_ = go_camera_1->AddComponent(Transform);
    transform_camera_1_->m_position = { 0, 0, 5 };
    //挂上 Camera 组件
    camera_1_ = go_camera_1->AddComponent(Camera);
    camera_1_->set_depth(0);


    last_frame_mouse_position_ = Input::mousePosition();
}

void LoginScene::Update() {
    camera_1_->SetView({ 0, 0, 0 }, { 0, 1, 0 });
    camera_1_->SetProjection(60, 16 / 9.0f, 0.01f, 1000.0f);

    camera_2_->SetView({ transform_camera_2_->m_position.x, 0, 0 }, { 0, 1, 0 });
    camera_2_->SetProjection(60, 16 / 9.0f, 0.01f, 1000.0f);

    if (Input::GetKeyDown(KEY_CODE_R)) {
        static float rotate_eulerAngle = 0.f;
        rotate_eulerAngle += 0.1f;
        transform_cube_->m_rotation.FromAngleAxis(Radian(rotate_eulerAngle), { 0, 1, 0 });
    }

    if (Input::GetKeyDown(KEY_CODE_LEFT_ALT) && Input::GetKeyDown(MOUSE_BUTTON_LEFT)) {
        float degrees = Input::mousePosition().x_ - last_frame_mouse_position_.x_;

        transform_camera_1_->m_position = Quaternion::GetQuaternionFromAngleAxis(Radian(Degree(-degrees)), { 0, 1, 0 }) * transform_camera_1_->m_position;
    }
    last_frame_mouse_position_ = Input::mousePosition();
    transform_camera_1_->m_position = transform_camera_1_->m_position * (10 - Input::mouse_scroll()) / 10.0f;
}
