#pragma once

#include "axis_aligned.h"
#include "math.hpp"
#include "matrix3.h"
#include "matrix4.h"
#include "quaternion.h"
#include "random.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"

#define Math_Min(x, y) (((x) < (y)) ? (x) : (y))
#define Math_Max(x, y) (((x) > (y)) ? (x) : (y))
#define Math_PIN(a, min_value, max_value) Math_MIN(max_value, Math_MAX(a, min_value))

#define Math_VALID_INDEX(idx, range) (((idx) >= 0) && ((idx) < (range)))
#define Math_PIN_INDEX(idx, range) Math_PIN(idx, 0, (range)-1)

#define Math_Sign(x) ((((x) > 0.0f) ? 1.0f : 0.0f) + (((x) < 0.0f) ? -1.0f : 0.0f))