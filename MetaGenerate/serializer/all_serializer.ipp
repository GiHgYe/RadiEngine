#pragma once
#include "meta/serializer/serializer.h"
#include "serializer\camera.serializer.gen.h"
#include "serializer\component.serializer.gen.h"
#include "serializer\quaternion.serializer.gen.h"
#include "serializer\matrix4.serializer.gen.h"
#include "serializer\vector3.serializer.gen.h"
#include "serializer\axis_aligned.serializer.gen.h"
#include "serializer\vector2.serializer.gen.h"
#include "serializer\vector4.serializer.gen.h"
#include "serializer\transform.serializer.gen.h"
#include "serializer\mesh_filter.serializer.gen.h"
#include "serializer\mesh_renderer.serializer.gen.h"
#include "serializer\ui_image.serializer.gen.h"
#include "serializer\login_scene.serializer.gen.h"

template<>
Json Serializer::Write(const Camera& instance){
    Json::object  ret_context;
    auto&&  json_context_0 = Serializer::Write(*(Component*)&instance);
    assert(json_context_0.is_object());
    auto&& json_context_map_0 = json_context_0.object_items();
    ret_context.insert(json_context_map_0.begin() , json_context_map_0.end());
    
    return  Json(ret_context);
}
template<>
Camera& Serializer::Read(const Json& json_context, Camera& instance){
    assert(json_context.is_object());
    Serializer::Read(json_context,*(Component*)&instance);

    return instance;
}
template<>
Json Serializer::Write(const Component& instance){
    Json::object  ret_context;
    
    
    return  Json(ret_context);
}
template<>
Component& Serializer::Read(const Json& json_context, Component& instance){
    assert(json_context.is_object());
    

    return instance;
}
template<>
Json Serializer::Write(const Quaternion& instance){
    Json::object  ret_context;
    
    ret_context.insert_or_assign("w", Serializer::Write(instance.w));
    ret_context.insert_or_assign("x", Serializer::Write(instance.x));
    ret_context.insert_or_assign("y", Serializer::Write(instance.y));
    ret_context.insert_or_assign("z", Serializer::Write(instance.z));
    return  Json(ret_context);
}
template<>
Quaternion& Serializer::Read(const Json& json_context, Quaternion& instance){
    assert(json_context.is_object());
    
    if(!json_context["w"].is_null()){
        Serializer::Read(json_context["w"], instance.w);
    }
    if(!json_context["x"].is_null()){
        Serializer::Read(json_context["x"], instance.x);
    }
    if(!json_context["y"].is_null()){
        Serializer::Read(json_context["y"], instance.y);
    }
    if(!json_context["z"].is_null()){
        Serializer::Read(json_context["z"], instance.z);
    }
    return instance;
}
template<>
Json Serializer::Write(const Matrix4x4_& instance){
    Json::object  ret_context;
    
    ret_context.insert_or_assign("v0", Serializer::Write(instance.v0));
    ret_context.insert_or_assign("v1", Serializer::Write(instance.v1));
    ret_context.insert_or_assign("v2", Serializer::Write(instance.v2));
    ret_context.insert_or_assign("v3", Serializer::Write(instance.v3));
    ret_context.insert_or_assign("v4", Serializer::Write(instance.v4));
    ret_context.insert_or_assign("v5", Serializer::Write(instance.v5));
    ret_context.insert_or_assign("v6", Serializer::Write(instance.v6));
    ret_context.insert_or_assign("v7", Serializer::Write(instance.v7));
    ret_context.insert_or_assign("v8", Serializer::Write(instance.v8));
    ret_context.insert_or_assign("v9", Serializer::Write(instance.v9));
    ret_context.insert_or_assign("v10", Serializer::Write(instance.v10));
    ret_context.insert_or_assign("v11", Serializer::Write(instance.v11));
    ret_context.insert_or_assign("v12", Serializer::Write(instance.v12));
    ret_context.insert_or_assign("v13", Serializer::Write(instance.v13));
    ret_context.insert_or_assign("v14", Serializer::Write(instance.v14));
    ret_context.insert_or_assign("v15", Serializer::Write(instance.v15));
    return  Json(ret_context);
}
template<>
Matrix4x4_& Serializer::Read(const Json& json_context, Matrix4x4_& instance){
    assert(json_context.is_object());
    
    if(!json_context["v0"].is_null()){
        Serializer::Read(json_context["v0"], instance.v0);
    }
    if(!json_context["v1"].is_null()){
        Serializer::Read(json_context["v1"], instance.v1);
    }
    if(!json_context["v2"].is_null()){
        Serializer::Read(json_context["v2"], instance.v2);
    }
    if(!json_context["v3"].is_null()){
        Serializer::Read(json_context["v3"], instance.v3);
    }
    if(!json_context["v4"].is_null()){
        Serializer::Read(json_context["v4"], instance.v4);
    }
    if(!json_context["v5"].is_null()){
        Serializer::Read(json_context["v5"], instance.v5);
    }
    if(!json_context["v6"].is_null()){
        Serializer::Read(json_context["v6"], instance.v6);
    }
    if(!json_context["v7"].is_null()){
        Serializer::Read(json_context["v7"], instance.v7);
    }
    if(!json_context["v8"].is_null()){
        Serializer::Read(json_context["v8"], instance.v8);
    }
    if(!json_context["v9"].is_null()){
        Serializer::Read(json_context["v9"], instance.v9);
    }
    if(!json_context["v10"].is_null()){
        Serializer::Read(json_context["v10"], instance.v10);
    }
    if(!json_context["v11"].is_null()){
        Serializer::Read(json_context["v11"], instance.v11);
    }
    if(!json_context["v12"].is_null()){
        Serializer::Read(json_context["v12"], instance.v12);
    }
    if(!json_context["v13"].is_null()){
        Serializer::Read(json_context["v13"], instance.v13);
    }
    if(!json_context["v14"].is_null()){
        Serializer::Read(json_context["v14"], instance.v14);
    }
    if(!json_context["v15"].is_null()){
        Serializer::Read(json_context["v15"], instance.v15);
    }
    return instance;
}
template<>
Json Serializer::Write(const Vector3& instance){
    Json::object  ret_context;
    
    ret_context.insert_or_assign("x", Serializer::Write(instance.x));
    ret_context.insert_or_assign("y", Serializer::Write(instance.y));
    ret_context.insert_or_assign("z", Serializer::Write(instance.z));
    return  Json(ret_context);
}
template<>
Vector3& Serializer::Read(const Json& json_context, Vector3& instance){
    assert(json_context.is_object());
    
    if(!json_context["x"].is_null()){
        Serializer::Read(json_context["x"], instance.x);
    }
    if(!json_context["y"].is_null()){
        Serializer::Read(json_context["y"], instance.y);
    }
    if(!json_context["z"].is_null()){
        Serializer::Read(json_context["z"], instance.z);
    }
    return instance;
}
template<>
Json Serializer::Write(const AxisAlignedBox& instance){
    Json::object  ret_context;
    
    ret_context.insert_or_assign("center", Serializer::Write(instance.m_center));
    ret_context.insert_or_assign("half_extent", Serializer::Write(instance.m_half_extent));
    ret_context.insert_or_assign("min_corner", Serializer::Write(instance.m_min_corner));
    ret_context.insert_or_assign("max_corner", Serializer::Write(instance.m_max_corner));
    return  Json(ret_context);
}
template<>
AxisAlignedBox& Serializer::Read(const Json& json_context, AxisAlignedBox& instance){
    assert(json_context.is_object());
    
    if(!json_context["center"].is_null()){
        Serializer::Read(json_context["center"], instance.m_center);
    }
    if(!json_context["half_extent"].is_null()){
        Serializer::Read(json_context["half_extent"], instance.m_half_extent);
    }
    if(!json_context["min_corner"].is_null()){
        Serializer::Read(json_context["min_corner"], instance.m_min_corner);
    }
    if(!json_context["max_corner"].is_null()){
        Serializer::Read(json_context["max_corner"], instance.m_max_corner);
    }
    return instance;
}
template<>
Json Serializer::Write(const Vector2& instance){
    Json::object  ret_context;
    
    ret_context.insert_or_assign("x", Serializer::Write(instance.x));
    ret_context.insert_or_assign("y", Serializer::Write(instance.y));
    return  Json(ret_context);
}
template<>
Vector2& Serializer::Read(const Json& json_context, Vector2& instance){
    assert(json_context.is_object());
    
    if(!json_context["x"].is_null()){
        Serializer::Read(json_context["x"], instance.x);
    }
    if(!json_context["y"].is_null()){
        Serializer::Read(json_context["y"], instance.y);
    }
    return instance;
}
template<>
Json Serializer::Write(const Vector4& instance){
    Json::object  ret_context;
    
    ret_context.insert_or_assign("x", Serializer::Write(instance.x));
    ret_context.insert_or_assign("y", Serializer::Write(instance.y));
    ret_context.insert_or_assign("z", Serializer::Write(instance.z));
    ret_context.insert_or_assign("w", Serializer::Write(instance.w));
    return  Json(ret_context);
}
template<>
Vector4& Serializer::Read(const Json& json_context, Vector4& instance){
    assert(json_context.is_object());
    
    if(!json_context["x"].is_null()){
        Serializer::Read(json_context["x"], instance.x);
    }
    if(!json_context["y"].is_null()){
        Serializer::Read(json_context["y"], instance.y);
    }
    if(!json_context["z"].is_null()){
        Serializer::Read(json_context["z"], instance.z);
    }
    if(!json_context["w"].is_null()){
        Serializer::Read(json_context["w"], instance.w);
    }
    return instance;
}
template<>
Json Serializer::Write(const Transform& instance){
    Json::object  ret_context;
    auto&&  json_context_0 = Serializer::Write(*(Component*)&instance);
    assert(json_context_0.is_object());
    auto&& json_context_map_0 = json_context_0.object_items();
    ret_context.insert(json_context_map_0.begin() , json_context_map_0.end());
    ret_context.insert_or_assign("position", Serializer::Write(instance.m_position));
    ret_context.insert_or_assign("scale", Serializer::Write(instance.m_scale));
    ret_context.insert_or_assign("rotation", Serializer::Write(instance.m_rotation));
    return  Json(ret_context);
}
template<>
Transform& Serializer::Read(const Json& json_context, Transform& instance){
    assert(json_context.is_object());
    Serializer::Read(json_context,*(Component*)&instance);
    if(!json_context["position"].is_null()){
        Serializer::Read(json_context["position"], instance.m_position);
    }
    if(!json_context["scale"].is_null()){
        Serializer::Read(json_context["scale"], instance.m_scale);
    }
    if(!json_context["rotation"].is_null()){
        Serializer::Read(json_context["rotation"], instance.m_rotation);
    }
    return instance;
}
template<>
Json Serializer::Write(const MeshFilter& instance){
    Json::object  ret_context;
    auto&&  json_context_0 = Serializer::Write(*(Component*)&instance);
    assert(json_context_0.is_object());
    auto&& json_context_map_0 = json_context_0.object_items();
    ret_context.insert(json_context_map_0.begin() , json_context_map_0.end());
    
    return  Json(ret_context);
}
template<>
MeshFilter& Serializer::Read(const Json& json_context, MeshFilter& instance){
    assert(json_context.is_object());
    Serializer::Read(json_context,*(Component*)&instance);

    return instance;
}
template<>
Json Serializer::Write(const MeshRenderer& instance){
    Json::object  ret_context;
    auto&&  json_context_0 = Serializer::Write(*(Component*)&instance);
    assert(json_context_0.is_object());
    auto&& json_context_map_0 = json_context_0.object_items();
    ret_context.insert(json_context_map_0.begin() , json_context_map_0.end());
    
    return  Json(ret_context);
}
template<>
MeshRenderer& Serializer::Read(const Json& json_context, MeshRenderer& instance){
    assert(json_context.is_object());
    Serializer::Read(json_context,*(Component*)&instance);

    return instance;
}
template<>
Json Serializer::Write(const UIImage& instance){
    Json::object  ret_context;
    auto&&  json_context_0 = Serializer::Write(*(Component*)&instance);
    assert(json_context_0.is_object());
    auto&& json_context_map_0 = json_context_0.object_items();
    ret_context.insert(json_context_map_0.begin() , json_context_map_0.end());
    
    return  Json(ret_context);
}
template<>
UIImage& Serializer::Read(const Json& json_context, UIImage& instance){
    assert(json_context.is_object());
    Serializer::Read(json_context,*(Component*)&instance);

    return instance;
}
template<>
Json Serializer::Write(const LoginScene& instance){
    Json::object  ret_context;
    auto&&  json_context_0 = Serializer::Write(*(Component*)&instance);
    assert(json_context_0.is_object());
    auto&& json_context_map_0 = json_context_0.object_items();
    ret_context.insert(json_context_map_0.begin() , json_context_map_0.end());
    
    return  Json(ret_context);
}
template<>
LoginScene& Serializer::Read(const Json& json_context, LoginScene& instance){
    assert(json_context.is_object());
    Serializer::Read(json_context,*(Component*)&instance);

    return instance;
}


