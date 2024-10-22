#pragma once
#include "..\ReCore\include\math\vector2.h"


template<>
Json Serializer::Write(const Vector2& instance);
template<>
Vector2& Serializer::Read(const Json& json_context, Vector2& instance);


