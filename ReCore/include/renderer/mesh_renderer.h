#pragma once
#include "math\math_headers.h"
#include "component/component.h"

class Material;
class MeshFilter;
class Texture2D;

REFLECTION_TYPE(MeshRenderer);
CLASS(MeshRenderer : public Component, WhiteListFields)
{
    REFLECTION_BODY(MeshRenderer)
public:
	MeshRenderer();
	~MeshRenderer();

    void SetMaterial(Material* material);
    Material* material() { return material_; }


    void Render();

private:
    Material* material_{};

    unsigned int vertex_buffer_object_ = 0;     //顶点缓冲区对象
    unsigned int element_buffer_object_ = 0;    //索引缓冲区对象
    unsigned int vertex_array_object_ = 0;      //顶点数组对象
};