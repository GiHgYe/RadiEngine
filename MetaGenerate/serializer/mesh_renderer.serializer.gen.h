#pragma once
#include "..\ReCore\include\renderer\mesh_renderer.h"
#include "serializer\component.serializer.gen.h"


template<>
Json Serializer::Write(const MeshRenderer& instance);
template<>
MeshRenderer& Serializer::Read(const Json& json_context, MeshRenderer& instance);


