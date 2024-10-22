#pragma once
#include "..\ReCore\include\math\vector4.h"


template<>
Json Serializer::Write(const Vector4& instance);
template<>
Vector4& Serializer::Read(const Json& json_context, Vector4& instance);


