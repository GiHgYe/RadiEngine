#include "login_scene.h"
#include "screen.h"
#include "control/key_code.h"
#include "component/game_object.h"
#include "component/transform.h"
#include "renderer/texture2d.h"
#include "renderer/mesh_filter.h"
#include "renderer/shader.h"
#include "renderer/material.h"
#include "renderer/mesh_renderer.h"
#include "renderer/camera.h"
#include "renderer/font.h"
#include "ui/ui_image.h"
#include <math/math_headers.h>

LoginScene::LoginScene() :Component()
{

}

void LoginScene::Awake() 
{
    //创建相机1 GameObject
    auto go_camera_1 = new GameObject("main_camera");
    //挂上 Transform 组件
    transform_camera_1_ = go_camera_1->AddComponent(Transform);
    transform_camera_1_->m_position = { 0, 0, 5 };
    //挂上 Camera 组件
    camera_1_ = go_camera_1->AddComponent(Camera);
    camera_1_->set_depth(0);
    camera_1_->set_culling_mask(0x01);

    last_frame_mouse_position_ = Input::mousePosition();

    CreateCube();
    CreateFont();
    CreateUI();
}

void LoginScene::Update() {
    camera_1_->SetView({ 0, 0, 0 }, { 0, 1, 0 });
    camera_1_->SetProjection(60, 16 / 9.0f, 0.01f, 1000.0f);

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


void LoginScene::CreateCube() {
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
    material->Parse("../asset/material/cube.mat");
    mesh_renderer->SetMaterial(material);

}

void LoginScene::CreateFont() {
    std::string str = "Captain";
    //生成文字贴图
    Font* font = Font::LoadFromFile("../asset/font/bahnschrift.ttf", 100);
    if (!font) exit(-1);
    std::vector<Font::Character*> character_vec = font->LoadStr(str);

    //遍历每个字符进行绘制
    int offset_x = 0;
    for (auto character : character_vec) {
        offset_x += 2;
        //因为FreeType生成的bitmap是上下颠倒的，所以这里UV坐标也要做对应翻转，将左上角作为零点。
        std::vector<MeshFilter::Vertex> vertex_vector = {
                {{-1.0f + offset_x, 2.0f, 1.0f},  {1.0f,0.0f,0.0f,1.0f},  {character->left_top_x_, character->right_bottom_y_}},
                {{ 1.0f + offset_x, 2.0f, 1.0f},  {1.0f,0.0f,0.0f,1.0f},  {character->right_bottom_x_, character->right_bottom_y_}},
                {{ 1.0f + offset_x,  4.0f, 1.0f}, {0.0f,1.0f,0.0f,1.0f},  {character->right_bottom_x_, character->left_top_y_}},
                {{-1.0f + offset_x,  4.0f, 1.0f}, {0.0f,1.0f,0.0f,1.0f},  {character->left_top_x_, character->left_top_y_}}
        };
        std::vector<unsigned short> index_vector = {
                0,1,2,
                0,2,3
        };

        //创建模型 GameObject
        auto go = new GameObject("quad_draw_font");
        go->set_layer(0x01);

        //挂上 Transform 组件
        auto transform = go->AddComponent(Transform);
        transform->m_position = { -8.f,0.f,0.f };

        //挂上 MeshFilter 组件
        auto mesh_filter = go->AddComponent(MeshFilter);
        mesh_filter->CreateMesh(vertex_vector, index_vector);

        //创建 Material
        material = new Material();//设置材质
        material->Parse("../asset/material/quad_draw_font.mat");

        //挂上 MeshRenderer 组件
        auto mesh_renderer = go->AddComponent(MeshRenderer);
        mesh_renderer->SetMaterial(material);

        //使用文字贴图
        material->SetTexture("u_diffuseMap0", font->font_texture());
    }
}

void LoginScene::CreateUI()
{
    //创建UI相机 GameObject
    auto go_camera_ui = new GameObject("ui_camera");

    auto transform_camera_ui = go_camera_ui->AddComponent(Transform);
    transform_camera_ui->m_position = Vector3(0, 0, 10);

    auto camera_ui = go_camera_ui->AddComponent(Camera);
    camera_ui->set_depth(1);
    camera_ui->set_culling_mask(0x02);
    camera_ui->set_clear_flag(GL_DEPTH_BUFFER_BIT);
    camera_ui->SetView({0, 0, 0}, {0, 1, 0});
    camera_ui->SetOrthographic(-Screen::width() / 2, Screen::width() / 2, -Screen::height() / 2, Screen::height() / 2, -100, 100);

    //加载图片
    auto texture2D = Texture2D::LoadFromFile("../asset/texture/checker.cpt");

    //创建UI GameObject
    auto go = new GameObject("image_mod_bag");
    go->set_layer(0x02);

    go->AddComponent(Transform)->m_scale = {0.1, 0.1, 0.1};

    auto ui_image = go->AddComponent(UIImage);
    ui_image->set_texture(texture2D);
}