#pragma once
#include "..\ReCore\include\math\vector3.h"


template<>
Json Serializer::Write(const Vector3& instance);
template<>
Vector3& Serializer::Read(const Json& json_context, Vector3& instance);


