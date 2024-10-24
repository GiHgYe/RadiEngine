#include "renderer/mesh_renderer.h"
#include "renderer/mesh_filter.h"
#include "renderer/material.h"
#include "renderer/shader.h"
#include "renderer/texture2d.h"
#include "renderer/camera.h"
#include "component/game_object.h"
#include "component/transform.h"
#include <glad.h>

MeshRenderer::MeshRenderer() {

}

MeshRenderer::~MeshRenderer() {

}

void MeshRenderer::SetMaterial(Material* material) {
    material_ = material;
}


void MeshRenderer::Render() 
{
    Camera* current_camera = Camera::current_camera();
    if (!current_camera) return;

    if ((current_camera->culling_mask() & game_object()->layer()) == 0x00) {
        return;
    }

    auto transform = game_object()->GetComponent(Transform);
    if (!transform) return;

    Matrix4x4 mvp = current_camera->projection_mat4() * current_camera->view_mat4() * transform->GetMatrix();

    auto mesh_filter = game_object()->GetComponent(MeshFilter);
    if (!mesh_filter) return;

    //获取`Shader`的`gl_program_id`，指定为目标Shader程序。
    GLuint shader_program_handle = material_->shader()->shader_program_handle();

    if (vertex_array_object_ == 0) {
        GLint vpos_location = glGetAttribLocation(shader_program_handle, "a_pos");
        GLint vcol_location = glGetAttribLocation(shader_program_handle, "a_color");
        GLint a_uv_location = glGetAttribLocation(shader_program_handle, "a_uv");

        //在GPU上创建缓冲区对象
        glGenBuffers(1, &vertex_buffer_object_);
        //将缓冲区对象指定为顶点缓冲区对象
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_);
        //上传顶点数据到缓冲区对象
        glBufferData(GL_ARRAY_BUFFER, mesh_filter->mesh()->vertex_num * sizeof(MeshFilter::Vertex), mesh_filter->mesh()->vertex_data, GL_STATIC_DRAW);

        //在GPU上创建缓冲区对象
        glGenBuffers(1, &element_buffer_object_);
        //将缓冲区对象指定为顶点索引缓冲区对象
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object_);
        //上传顶点索引数据到缓冲区对象
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_filter->mesh()->vertex_index_num * sizeof(unsigned short), mesh_filter->mesh()->vertex_index_data, GL_STATIC_DRAW);

        glGenVertexArrays(1, &vertex_array_object_);

        //设置VAO
        glBindVertexArray(vertex_array_object_);
        {
            //指定当前使用的VBO
            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_);
            //将Shader变量(a_pos)和顶点坐标VBO句柄进行关联，最后的0表示数据偏移量。
            glVertexAttribPointer(vpos_location, 3, GL_FLOAT, false, sizeof(MeshFilter::Vertex), 0);
            //启用顶点Shader属性(a_normal)，指定与顶点颜色数据进行关联
            glVertexAttribPointer(vcol_location, 4, GL_FLOAT, false, sizeof(MeshFilter::Vertex), (void*)(sizeof(float) * 3));
            //将Shader变量(a_uv)和顶点UV坐标VBO句柄进行关联，最后的0表示数据偏移量。
            glVertexAttribPointer(a_uv_location, 2, GL_FLOAT, false, sizeof(MeshFilter::Vertex), (void*)(sizeof(float) * (3 + 4)));

            glEnableVertexAttribArray(vpos_location);
            glEnableVertexAttribArray(vcol_location);
            glEnableVertexAttribArray(a_uv_location);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object_);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    glUseProgram(shader_program_handle);
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);//开启背面剔除
        //上传mvp矩阵
        glUniformMatrix4fv(glGetUniformLocation(shader_program_handle, "u_mvp"), 1, GL_TRUE, &mvp[0][0]);

        //从Pass节点拿到保存的Texture
        std::vector<std::pair<std::string, Texture2D*>> textures = material_->textures();
        for (int texture_index = 0; texture_index < textures.size(); ++texture_index) {
            GLint u_texture_location = glGetUniformLocation(shader_program_handle, textures[texture_index].first.c_str());
            //激活纹理单元0
            glActiveTexture(GL_TEXTURE0 + texture_index);
            //将加载的图片纹理句柄，绑定到纹理单元0的Texture2D上。
            glBindTexture(GL_TEXTURE_2D, textures[texture_index].second->texture_handle());
            //设置Shader程序从纹理单元0读取颜色数据
            glUniform1i(u_texture_location, texture_index);
        }

        glBindVertexArray(vertex_array_object_);
        {
            glDrawElements(GL_TRIANGLES, mesh_filter->mesh()->vertex_index_num, GL_UNSIGNED_SHORT, 0);//使用顶点索引进行绘制，最后的0表示数据偏移量。
        }
        glBindVertexArray(0);
    }
}