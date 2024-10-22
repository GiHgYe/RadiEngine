#pragma once
#include "..\ReCore\include\math\matrix4.h"


template<>
Json Serializer::Write(const Matrix4x4_& instance);
template<>
Matrix4x4_& Serializer::Read(const Json& json_context, Matrix4x4_& instance);


