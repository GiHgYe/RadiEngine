#pragma once
#include "meta\reflection\reflection_register.h"
#include "meta\reflection\reflection.h"
#include "serializer\all_serializer.h"
#include "reflection\component.reflection.gen.h"
#include "reflection\quaternion.reflection.gen.h"
#include "reflection\matrix4.reflection.gen.h"
#include "reflection\vector3.reflection.gen.h"
#include "reflection\axis_aligned.reflection.gen.h"
#include "reflection\vector2.reflection.gen.h"
#include "reflection\vector4.reflection.gen.h"
#include "reflection\transform.reflection.gen.h"
#include "reflection\material.reflection.gen.h"
#include "reflection\mesh_filter.reflection.gen.h"
#include "reflection\mesh_renderer.reflection.gen.h"


namespace Reflection{
    void TypeMetaRegister::metaRegister(){
        TypeWrappersRegister::Component();
        TypeWrappersRegister::Quaternion();
        TypeWrappersRegister::Matrix4();
        TypeWrappersRegister::Vector3();
        TypeWrappersRegister::AxisAligned();
        TypeWrappersRegister::Vector2();
        TypeWrappersRegister::Vector4();
        TypeWrappersRegister::Transform();
        TypeWrappersRegister::Material();
        TypeWrappersRegister::MeshFilter();
        TypeWrappersRegister::MeshRenderer();
    }
}

