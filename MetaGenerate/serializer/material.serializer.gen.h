#pragma once
#include "..\ReCore\include\renderer\material.h"
#include "serializer\component.serializer.gen.h"


template<>
Json Serializer::Write(const Material& instance);
template<>
Material& Serializer::Read(const Json& json_context, Material& instance);


