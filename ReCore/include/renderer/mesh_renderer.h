#pragma once
#include "math\math_headers.h"
#include "component/component.h"

class Material;
class MeshFilter;
class Texture2D;

REFLECTION_TYPE(MeshRenderer)
CLASS(MeshRenderer : public Component, WhiteListFields)
{
    REFLECTION_BODY(MeshRenderer)
public:
	MeshRenderer();
	~MeshRenderer();

    void SetMaterial(Material* material);
    Material* material() { return material_; }

    void SetMeshFilter(MeshFilter* mesh_filter);

    void SetView(Matrix4x4 view);
    void SetProjection(Matrix4x4 projection);

    void Render();

private:
    Material* material_{};

    Matrix4x4 view_;
    Matrix4x4 projection_;

    unsigned int vertex_buffer_object_ = 0;     //顶点缓冲区对象
    unsigned int element_buffer_object_ = 0;    //索引缓冲区对象
    unsigned int vertex_array_object_ = 0;      //顶点数组对象
};