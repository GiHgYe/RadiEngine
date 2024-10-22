#pragma once
#include "meta/reflection/reflection.h"
#include "math.hpp"
#include <cassert>
#include <cmath>

REFLECTION_TYPE(Vector2)
CLASS(Vector2, Fields)
{
	REFLECTION_BODY(Vector2);
public:
	float x{ 0.0f }, y{ 0.0f };

	Vector2() = default;

	Vector2(float _x, float _y) : x(_x), y(_y) {}

	explicit Vector2(float scaler) : x(scaler), y(scaler) {}

	explicit Vector2(const float v[2]) : x(v[0]), y(v[1]) {}

	explicit Vector2(float* const r) : x(r[0]), y(r[1]) {}

	float* ptr() { return &x; }

	const float* ptr() const { return &x; }

	float operator[](size_t i) const
	{
		assert(i < 2);
		return (i == 0 ? x : y);
	}

	float& operator[](size_t i)
	{
		assert(i < 2);
		return (i == 0 ? x : y);
	}

	bool operator==(const Vector2& rhs) const { return (x == rhs.x && y == rhs.y); }

	bool operator!=(const Vector2& rhs) const { return (x != rhs.x || y != rhs.y); }

	Vector2 operator+(const Vector2& rhs) const { return Vector2(x + rhs.x, y + rhs.y); }

	Vector2 operator-(const Vector2& rhs) const { return Vector2(x - rhs.x, y - rhs.y); }

	Vector2 operator*(float scalar) const { return Vector2(x * scalar, y * scalar); }

	Vector2 operator*(const Vector2& rhs) const { return Vector2(x * rhs.x, y * rhs.y); }

	Vector2 operator/(float scale) const
	{
		assert(scale != 0.0);
		float inv = 1.0f / scale;
		return Vector2(x * inv, y * inv);
	}

	Vector2 operator/(const Vector2& rhs) const { return Vector2(x / rhs.x, y / rhs.y); }

	const Vector2& operator+() const { return *this; }

	Vector2 operator-() const { return Vector2(-x, -y); }

	friend Vector2 operator*(float scalar, const Vector2& rhs) { return Vector2(scalar * rhs.x, scalar * rhs.y); }

	friend Vector2 operator/(float fScalar, const Vector2& rhs) { return Vector2(fScalar / rhs.x, fScalar / rhs.y); }

	friend Vector2 operator+(const Vector2& lhs, float rhs) { return Vector2(lhs.x + rhs, lhs.y + rhs); }

	friend Vector2 operator+(float lhs, const Vector2& rhs) { return Vector2(lhs + rhs.x, lhs + rhs.y); }

	friend Vector2 operator-(const Vector2& lhs, float rhs) { return Vector2(lhs.x - rhs, lhs.y - rhs); }

	friend Vector2 operator-(float lhs, const Vector2& rhs) { return Vector2(lhs - rhs.x, lhs - rhs.y); }

	Vector2& operator+=(const Vector2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vector2& operator+=(float scalar)
	{
		x += scalar;
		y += scalar;
		return *this;
	}

	Vector2& operator-=(const Vector2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	Vector2& operator-=(float scalar)
	{
		x -= scalar;
		y -= scalar;
		return *this;
	}

	Vector2& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vector2& operator*=(const Vector2& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}

	Vector2& operator/=(float scalar)
	{
		assert(scalar != 0.0);
		float inv = 1.0f / scalar;
		x *= inv;
		y *= inv;
		return *this;
	}

	Vector2& operator/=(const Vector2& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}

	float Length() const { return std::hypot(x, y); }

	float SquaredLength() const { return x * x + y * y; }

	float Distance(const Vector2& rhs) const { return (*this - rhs).Length(); }

	float SquaredDistance(const Vector2& rhs) const { return (*this - rhs).SquaredLength(); }

	float DotProduct(const Vector2& vec) const { return x * vec.x + y * vec.y; }

	float Normalise()
	{
		float lengh = std::hypot(x, y);
		if (lengh > 0.0f)
		{
			float inv_length = 1.0f / lengh;
			x *= inv_length;
			y *= inv_length;
		}
		return lengh;
	}

	float GetX() const { return x; }
	float GetY() const { return y; }

	void SetX(float value) { x = value; }
	void SetY(float value) { y = value; }

	Vector2 MidPoint(const Vector2& vec) const { return Vector2((x + vec.x) * 0.5f, (y + vec.y) * 0.5f); }

	bool operator<(const Vector2& rhs) const { return x < rhs.x && y < rhs.y; }

	bool operator>(const Vector2& rhs) const { return x > rhs.x && y > rhs.y; }

	void MakeFloor(const Vector2& cmp)
	{
		if (cmp.x < x) x = cmp.x;
		if (cmp.y < y) y = cmp.y;
	}

	void MakeCeil(const Vector2& cmp)
	{
		if (cmp.x > x) x = cmp.x;
		if (cmp.y > y) y = cmp.y;
	}

	Vector2 Perpendicular(void) const { return Vector2(-y, x); }

	float CrossProduct(const Vector2& rhs) const { return x * rhs.y - y * rhs.x; }

	bool IsZeroLength(void) const
	{
		float sqlen = (x * x) + (y * y);
		return (sqlen < (Float_EPSILON * Float_EPSILON));
	}

	Vector2 normalisedCopy(void) const
	{
		Vector2 ret = *this;
		ret.Normalise();
		return ret;
	}

	Vector2 Reflect(const Vector2& normal) const
	{
		return Vector2(*this - (2 * this->DotProduct(normal) * normal));
	}

	bool isNaN() const { return Math::IsNan(x) || Math::IsNan(y); }

	static Vector2 lerp(const Vector2& lhs, const Vector2& rhs, float alpha) { return lhs + alpha * (rhs - lhs); }

	static const Vector2 ZERO;
	static const Vector2 UNIT_X;
	static const Vector2 UNIT_Y;
	static const Vector2 NEGATIVE_UNIT_X;
	static const Vector2 NEGATIVE_UNIT_Y;
	static const Vector2 UNIT_SCALE;

};

