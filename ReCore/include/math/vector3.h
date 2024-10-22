#pragma once
#include "meta/reflection/reflection.h"
#include "math.hpp"
#include "quaternion.h"
#include <cassert>


REFLECTION_TYPE(Vector3)
CLASS(Vector3, Fields)
{
	REFLECTION_BODY(Vector3);
public:
	float x{ 0.f };
	float y{ 0.f };
	float z{ 0.f };

public:
	Vector3() = default;
	Vector3(float x_) : x{ x_ }, y{ x_ }, z{ x_ } {}
	Vector3(float x_, float y_, float z_) : x{ x_ }, y{ y_ }, z{ z_ } {}
	Vector3(const Vector4& v);
	explicit Vector3(const float coords[3]) : x{ coords[0] }, y{ coords[1] }, z{ coords[2] } {}

	float operator[](size_t i) const
	{
		assert(i < 3);
		return *(&x + i);
	}

	float& operator[](size_t i)
	{
		assert(i < 3);
		return *(&x + i);
	}
	
	float* ptr() { return &x; }
	
	const float* ptr() const { return &x; }

	void operator=(const Vector4& rhs);

	bool operator==(const Vector3 & rhs) const { return (x == rhs.x && y == rhs.y && z == rhs.z); }

	bool operator!=(const Vector3 & rhs) const { return x != rhs.x || y != rhs.y || z != rhs.z; }

	// arithmetic operations
	Vector3 operator+(const Vector3 & rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }

	Vector3 operator-(const Vector3 & rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }

	Vector3 operator*(float scalar) const { return Vector3(x * scalar, y * scalar, z * scalar); }

	Vector3 operator*(const Vector3 & rhs) const { return Vector3(x * rhs.x, y * rhs.y, z * rhs.z); }

	Vector3 operator/(float scalar) const
	{
		//assert(scalar != 0.0);
		return Vector3(x / scalar, y / scalar, z / scalar);
	}

	Vector3 operator/(const Vector3 & rhs) const
	{
		//assert((rhs.x != 0 && rhs.y != 0 && rhs.z != 0));
		return Vector3(x / rhs.x, y / rhs.y, z / rhs.z);
	}

	const Vector3& operator+() const { return *this; }

	Vector3 operator-() const { return Vector3(-x, -y, -z); }

	// overloaded operators to help Vector3
	friend Vector3 operator*(float scalar, const Vector3 & rhs)
	{
		return Vector3(scalar * rhs.x, scalar * rhs.y, scalar * rhs.z);
	}

	friend Vector3 operator/(float scalar, const Vector3 & rhs)
	{
		//assert(rhs.x != 0 && rhs.y != 0 && rhs.z != 0);
		return Vector3(scalar / rhs.x, scalar / rhs.y, scalar / rhs.z);
	}

	friend Vector3 operator+(const Vector3 & lhs, float rhs)
	{
		return Vector3(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
	}

	friend Vector3 operator+(float lhs, const Vector3 & rhs)
	{
		return Vector3(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z);
	}

	friend Vector3 operator-(const Vector3 & lhs, float rhs)
	{
		return Vector3(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
	}

	friend Vector3 operator-(float lhs, const Vector3 & rhs)
	{
		return Vector3(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z);
	}

	// arithmetic updates
	Vector3& operator+=(const Vector3 & rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	Vector3& operator+=(float scalar)
	{
		x += scalar;
		y += scalar;
		z += scalar;
		return *this;
	}

	Vector3& operator-=(const Vector3 & rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	Vector3& operator-=(float scalar)
	{
		x -= scalar;
		y -= scalar;
		z -= scalar;
		return *this;
	}

	Vector3& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	Vector3& operator*=(const Vector3 & rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}

	Vector3& operator/=(float scalar)
	{
		assert(scalar != 0.0);
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}

	Vector3& operator/=(const Vector3 & rhs)
	{
		assert(rhs.x != 0 && rhs.y != 0 && rhs.z != 0);
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		return *this;
	}

	float Length() const { return std::hypot(x, y, z); }

	float SquaredLength() const { return x * x + y * y + z * z; }

	float Distance(const Vector3 & rhs) const { return (*this - rhs).Length(); }

	float SquaredDistance(const Vector3 & rhs) const { return (*this - rhs).SquaredLength(); }

	float DotProduct(const Vector3 & vec) const { return x * vec.x + y * vec.y + z * vec.z; }

	void Normalise()
	{
		float Length = std::hypot(x, y, z);
		if (Length == 0.f)
			return;

		float inv_lengh = 1.0f / Length;
		x *= inv_lengh;
		y *= inv_lengh;
		z *= inv_lengh;
	}

	Vector3 CrossProduct(const Vector3 & rhs) const
	{
		return Vector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
	}

	void MakeFloor(const Vector3 & cmp)
	{
		if (cmp.x < x)
			x = cmp.x;
		if (cmp.y < y)
			y = cmp.y;
		if (cmp.z < z)
			z = cmp.z;
	}

	void MakeCeil(const Vector3 & cmp)
	{
		if (cmp.x > x)
			x = cmp.x;
		if (cmp.y > y)
			y = cmp.y;
		if (cmp.z > z)
			z = cmp.z;
	}

	Radian AngleBetween(const Vector3 & dest) const
	{
		float len_product = Length() * dest.Length();

		// Divide by zero check
		if (len_product < 1e-6f)
			len_product = 1e-6f;

		float f = DotProduct(dest) / len_product;

		f = Math::Clamp(f, (float)-1.0, (float)1.0);
		return Math::Acos(f);
	}
	/** Gets the shortest arc quaternion to rotate this vector to the destination
	vector.
	@remarks
	If you call this with a dest vector that is close to the inverse
	of this vector, we will rotate 180 degrees around the 'fallbackAxis'
	(if specified, or a generated axis if not) since in this case
	ANY axis of rotation is valid.
	*/

	Quaternion GetRotationTo(const Vector3& dest, const Vector3& fallback_axis = Vector3::ZERO) const
	{
		// Based on Stan Melax's article in Game Programming Gems
		Quaternion q;
		// Copy, since cannot modify local
		Vector3 v0 = *this;
		Vector3 v1 = dest;
		v0.Normalise();
		v1.Normalise();
		float d = v0.DotProduct(v1);
		// If dot == 1, vectors are the same
		if (d >= 1.0f)
		{
			return Quaternion::IDENTITY;
		}
		if (d < (1e-6f - 1.0f))
		{
			if (fallback_axis != Vector3::ZERO)
			{
				// rotate 180 degrees about the fall back axis
				q.FromAngleAxis(Radian(Math_PI), fallback_axis);
			}
			else
			{
				// Generate an axis
				Vector3 axis = Vector3::UNIT_X.CrossProduct(*this);
				if (axis.IsZeroLength()) // pick another if collinear
					axis = Vector3::UNIT_Y.CrossProduct(*this);
				axis.Normalise();
				q.FromAngleAxis(Radian(Math_PI), axis);
			}
		}
		else
		{
			float s = Math::Sqrt((1 + d) * 2);
			float invs = 1 / s;
			Vector3 c = v0.CrossProduct(v1);
			q.x = c.x * invs;
			q.y = c.y * invs;
			q.z = c.z * invs;
			q.w = s * 0.5f;
			q.Normalize();
		}
		return q;
	}

	bool IsZeroLength(void) const
	{
		float sqlen = (x * x) + (y * y) + (z * z);
		return (sqlen < (1e-06 * 1e-06));
	}

	bool IsZero() const { return x == 0.f && y == 0.f && z == 0.f; }

	Vector3 NormalisedCopy(void) const
	{
		Vector3 ret = *this;
		ret.Normalise();
		return ret;
	}

	Vector3 Reflect(const Vector3 & normal) const
	{
		return Vector3(*this - (2 * this->DotProduct(normal) * normal));
	}

	Vector3 Project(const Vector3 & normal) const { return Vector3(*this - (this->DotProduct(normal) * normal)); }

	Vector3 AbsoluteCopy() const { return Vector3(fabsf(x), fabsf(y), fabsf(z)); }

	static Vector3 Lerp(const Vector3 & lhs, const Vector3 & rhs, float alpha) { return lhs + alpha * (rhs - lhs); }

	static Vector3 Clamp(const Vector3 & v, const Vector3 & min, const Vector3 & max)
	{
		return Vector3(Math::Clamp(v.x, min.x, max.x), Math::Clamp(v.y, min.y, max.y), Math::Clamp(v.z, min.z, max.z));
	}

	static float GetMaxElement(const Vector3 & v) { return Math::GetMaxElement(v.x, v.y, v.z); }
	bool         IsNaN() const { return Math::IsNan(x) || Math::IsNan(y) || Math::IsNan(z); }
	// special points
	static const Vector3 ZERO;
	static const Vector3 UNIT_X;
	static const Vector3 UNIT_Y;
	static const Vector3 UNIT_Z;
	static const Vector3 NEGATIVE_UNIT_X;
	static const Vector3 NEGATIVE_UNIT_Y;
	static const Vector3 NEGATIVE_UNIT_Z;
	static const Vector3 UNIT_SCALE;
};

inline Vector3 MaxVector(const Vector3& v1, const Vector3& v2) {
	Vector3 res = v1;
	if (v1.x < v2.x)
		res.x = v2.x;
	if (v1.y < v2.y)
		res.y = v2.y;
	if (v1.z < v2.z)
		res.z = v2.z;
	return res;
}

inline Vector3 MinVector(const Vector3& v1, const Vector3& v2) {
	Vector3 res = v1;
	if (v1.x > v2.x)
		res.x = v2.x;
	if (v1.y > v2.y)
		res.y = v2.y;
	if (v1.z > v2.z)
		res.z = v2.z;
	return res;
}
