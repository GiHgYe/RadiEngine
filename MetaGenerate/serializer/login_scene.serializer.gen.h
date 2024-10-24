#pragma once
#include "..\SandBox\include\login_scene.h"
#include "serializer\component.serializer.gen.h"


template<>
Json Serializer::Write(const LoginScene& instance);
template<>
LoginScene& Serializer::Read(const Json& json_context, LoginScene& instance);


