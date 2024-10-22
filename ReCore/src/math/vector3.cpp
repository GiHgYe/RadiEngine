#include "math/vector3.h"
#include "math/vector4.h"

const Vector3 Vector3::ZERO(0, 0, 0);
const Vector3 Vector3::UNIT_X(1, 0, 0);
const Vector3 Vector3::UNIT_Y(0, 1, 0);
const Vector3 Vector3::UNIT_Z(0, 0, 1);
const Vector3 Vector3::NEGATIVE_UNIT_X(-1, 0, 0);
const Vector3 Vector3::NEGATIVE_UNIT_Y(0, -1, 0);
const Vector3 Vector3::NEGATIVE_UNIT_Z(0, 0, -1);
const Vector3 Vector3::UNIT_SCALE(1, 1, 1);

Vector3::Vector3(const Vector4& v) { x = v.x; y = v.y; z = v.z; }

void Vector3::operator=(const Vector4& rhs) { x = rhs.x; y = rhs.y; z = rhs.z; }
