#pragma once
#include "random.h"

//#include <algorithm>
#include <cmath>

#define CMP(x, y) (fabsf(x - y) < FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))))

static const float Math_POS_INFINITY = std::numeric_limits<float>::infinity();
static const float Math_NEG_INFINITY = -std::numeric_limits<float>::infinity();
static const float Math_PI = 3.14159265358979323846264338327950288f;
static const float Math_ONE_OVER_PI = 1.0f / Math_PI;
static const float Math_TWO_PI = 2.0f * Math_PI;
static const float Math_HALF_PI = 0.5f * Math_PI;
static const float Math_fDeg2Rad = Math_PI / 180.0f;
static const float Math_fRad2Deg = 180.0f / Math_PI;
static const float Math_LOG2 = log(2.0f);
static const float Math_EPSILON = 1e-6f;

static const float Float_EPSILON = FLT_EPSILON;
static const float Double_EPSILON = DBL_EPSILON;

class Radian;
class Angle;
class Degree;

class Vector2;
class Vector3;
class Vector4;
class Matrix3x3;
class Matrix4x4;
class Quaternion;

class Radian
{
	float m_rad;

public:
	explicit Radian(float r = 0) : m_rad(r) {}
	explicit Radian(const Degree& d);
	Radian& operator=(float f)
	{
		m_rad = f;
		return *this;
	}
	Radian& operator=(const Degree& d);

	float ValueRadians() const { return m_rad; }
	float ValueDegrees() const; // see bottom of this file
	float ValueAngleUnits() const;

	void SetValue(float f) { m_rad = f; }

	const Radian& operator+() const { return *this; }
	Radian        operator+(const Radian& r) const { return Radian(m_rad + r.m_rad); }
	Radian        operator+(const Degree& d) const;
	Radian& operator+=(const Radian& r)
	{
		m_rad += r.m_rad;
		return *this;
	}
	Radian& operator+=(const Degree& d);
	Radian  operator-() const { return Radian(-m_rad); }
	Radian  operator-(const Radian& r) const { return Radian(m_rad - r.m_rad); }
	Radian  operator-(const Degree& d) const;
	Radian& operator-=(const Radian& r)
	{
		m_rad -= r.m_rad;
		return *this;
	}
	Radian& operator-=(const Degree& d);
	Radian  operator*(float f) const { return Radian(m_rad * f); }
	Radian  operator*(const Radian& f) const { return Radian(m_rad * f.m_rad); }
	Radian& operator*=(float f)
	{
		m_rad *= f;
		return *this;
	}
	Radian  operator/(float f) const { return Radian(m_rad / f); }
	Radian& operator/=(float f)
	{
		m_rad /= f;
		return *this;
	}

	bool operator<(const Radian& r) const { return m_rad < r.m_rad; }
	bool operator<=(const Radian& r) const { return m_rad <= r.m_rad; }
	bool operator==(const Radian& r) const { return m_rad == r.m_rad; }
	bool operator!=(const Radian& r) const { return m_rad != r.m_rad; }
	bool operator>=(const Radian& r) const { return m_rad >= r.m_rad; }
	bool operator>(const Radian& r) const { return m_rad > r.m_rad; }
};

class Degree
{
	float m_deg; // if you get an error here - make sure to define/typedef 'float' first

public:
	explicit Degree(float d = 0) : m_deg(d) {}
	explicit Degree(const Radian& r) : m_deg(r.ValueDegrees()) {}
	Degree& operator=(float f)
	{
		m_deg = f;
		return *this;
	}
	Degree& operator=(const Degree& d) = default;
	Degree& operator=(const Radian& r)
	{
		m_deg = r.ValueDegrees();
		return *this;
	}

	float ValueDegrees() const { return m_deg; }
	float ValueRadians() const; // see bottom of this file
	float ValueAngleUnits() const;

	const Degree& operator+() const { return *this; }
	Degree        operator+(const Degree& d) const { return Degree(m_deg + d.m_deg); }
	Degree        operator+(const Radian& r) const { return Degree(m_deg + r.ValueDegrees()); }
	Degree& operator+=(const Degree& d)
	{
		m_deg += d.m_deg;
		return *this;
	}
	Degree& operator+=(const Radian& r)
	{
		m_deg += r.ValueDegrees();
		return *this;
	}
	Degree  operator-() const { return Degree(-m_deg); }
	Degree  operator-(const Degree& d) const { return Degree(m_deg - d.m_deg); }
	Degree  operator-(const Radian& r) const { return Degree(m_deg - r.ValueDegrees()); }
	Degree& operator-=(const Degree& d)
	{
		m_deg -= d.m_deg;
		return *this;
	}
	Degree& operator-=(const Radian& r)
	{
		m_deg -= r.ValueDegrees();
		return *this;
	}
	Degree  operator*(float f) const { return Degree(m_deg * f); }
	Degree  operator*(const Degree& f) const { return Degree(m_deg * f.m_deg); }
	Degree& operator*=(float f)
	{
		m_deg *= f;
		return *this;
	}
	Degree  operator/(float f) const { return Degree(m_deg / f); }
	Degree& operator/=(float f)
	{
		m_deg /= f;
		return *this;
	}

	bool operator<(const Degree& d) const { return m_deg < d.m_deg; }
	bool operator<=(const Degree& d) const { return m_deg <= d.m_deg; }
	bool operator==(const Degree& d) const { return m_deg == d.m_deg; }
	bool operator!=(const Degree& d) const { return m_deg != d.m_deg; }
	bool operator>=(const Degree& d) const { return m_deg >= d.m_deg; }
	bool operator>(const Degree& d) const { return m_deg > d.m_deg; }
};

class Angle
{
	float m_angle;

public:
	explicit Angle(float angle) : m_angle(angle) {}
	Angle() { m_angle = 0; }

	explicit operator Radian() const;
	explicit operator Degree() const;
};

class Math
{
private:
	enum class AngleUnit
	{
		AU_DEGREE,
		AU_RADIAN
	};

	static AngleUnit k_AngleUnit;

public:
	Math();

	static float Abs(float value) { return std::fabs(value); }
	static bool  IsNan(float f) { return std::isnan(f); }
	static float Sqr(float value) { return value * value; }
	static float Sqrt(float fValue) { return std::sqrt(fValue); }
	static float InvSqrt(float value) { return 1.f / sqrt(value); }
	static bool  RealEqual(float a, float b, float tolerance = std::numeric_limits<float>::epsilon());
	static float Clamp(float v, float min, float max) { return std::clamp(v, min, max); }
	static float GetMaxElement(float x, float y, float z) { return std::max<float>({ x, y, z }); }

	static float DegreesToRadians(float degrees);
	static float RadiansToDegrees(float radians);
	static float AngleUnitsToRadians(float units);
	static float RadiansToAngleUnits(float radians);
	static float AngleUnitsToDegrees(float units);
	static float DegreesToAngleUnits(float degrees);

	static float  Sin(const Radian& rad) { return std::sin(rad.ValueRadians()); }
	static float  Sin(float value) { return std::sin(value); }
	static float  Cos(const Radian& rad) { return std::cos(rad.ValueRadians()); }
	static float  Cos(float value) { return std::cos(value); }
	static float  Tan(const Radian& rad) { return std::tan(rad.ValueRadians()); }
	static float  Tan(float value) { return std::tan(value); }
	static Radian Acos(float value);
	static Radian Asin(float value);
	static Radian Atan(float value) { return Radian(std::atan(value)); }
	static Radian Atan2(float y_v, float x_v) { return Radian(std::atan2(y_v, x_v)); }

	template<typename T>
	static constexpr T Max(const T A, const T B) { return std::max<T>(A, B); }

	template<typename T>
	static constexpr T Min(const T A, const T B) { return std::min<T>(A, B); }

	template<typename T>
	static constexpr T Max3(const T A, const T B, const T C) { return std::max<T>({ A, B, C }); }

	template<typename T>
	static constexpr T Min3(const T A, const T B, const T C)
	{
		return std::min<T>({ A, B, C });
	}

	static Matrix4x4 MakeViewMatrix(const Vector3& position, const Quaternion& orientation, const Matrix4x4* reflect_matrix = nullptr);

	static Matrix4x4 MakeLookAtMatrix(const Vector3& eye_position, const Vector3& target_position, const Vector3& up_dir);

	static Matrix4x4 MakePerspectiveMatrix(Radian fovy, float aspect, float znear, float zfar);

	static Matrix4x4 MakeOrthographicProjectionMatrix(float left, float right, float bottom, float top, float znear, float zfar);

	static Matrix4x4 MakeOrthographicProjectionMatrix01(float left, float right, float bottom, float top, float znear, float zfar);
};



inline Radian::Radian(const Degree& d) : m_rad(d.ValueRadians()) {}
inline Radian& Radian::operator=(const Degree& d)
{
	m_rad = d.ValueRadians();
	return *this;
}
inline Radian Radian::operator+(const Degree& d) const { return Radian(m_rad + d.ValueRadians()); }
inline Radian& Radian::operator+=(const Degree& d)
{
	m_rad += d.ValueRadians();
	return *this;
}
inline Radian Radian::operator-(const Degree& d) const { return Radian(m_rad - d.ValueRadians()); }
inline Radian& Radian::operator-=(const Degree& d)
{
	m_rad -= d.ValueRadians();
	return *this;
}

inline float Radian::ValueDegrees() const { return Math::RadiansToDegrees(m_rad); }

inline float Radian::ValueAngleUnits() const { return Math::RadiansToAngleUnits(m_rad); }

inline float Degree::ValueRadians() const { return Math::DegreesToRadians(m_deg); }

inline float Degree::ValueAngleUnits() const { return Math::DegreesToAngleUnits(m_deg); }

inline Angle::operator Radian() const { return Radian(Math::AngleUnitsToRadians(m_angle)); }

inline Angle::operator Degree() const { return Degree(Math::AngleUnitsToDegrees(m_angle)); }

inline Radian operator*(float a, const Radian& b) { return Radian(a * b.ValueRadians()); }

inline Radian operator/(float a, const Radian& b) { return Radian(a / b.ValueRadians()); }

inline Degree operator*(float a, const Degree& b) { return Degree(a * b.ValueDegrees()); }

inline Degree operator/(float a, const Degree& b) { return Degree(a / b.ValueDegrees()); }
