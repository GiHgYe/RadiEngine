#pragma once
#include "..\ReCore\include\ui\ui_image.h"
#include "serializer\component.serializer.gen.h"


template<>
Json Serializer::Write(const UIImage& instance);
template<>
UIImage& Serializer::Read(const Json& json_context, UIImage& instance);


