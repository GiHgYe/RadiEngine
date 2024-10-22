#pragma once
#include "..\ReCore\include\renderer\mesh_filter.h"
#include "serializer\component.serializer.gen.h"


template<>
Json Serializer::Write(const MeshFilter& instance);
template<>
MeshFilter& Serializer::Read(const Json& json_context, MeshFilter& instance);


