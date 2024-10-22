#include <iostream>
#define SOL_ALL_SAFETIES_ON 1
#include "sol/sol.hpp"
extern "C"{
#include "luasocket.h"
}
#include "math/math_headers.h"
#include "reflection/all_reflection.h"


using namespace std;



int main()
{
	sol::state lua;
	lua.open_libraries();
	lua.require("socket.core", luaopen_socket_core, true);

	auto math_table = lua["Cpp"].get_or_create<sol::table>();

	math_table.set("Pi", Math_PI);

	math_table.set_function("Abs", &Math::Abs);
	math_table.set_function("IsNan", &Math::IsNan);
	math_table.set_function("Sqr", &Math::Sqr);
	math_table.set_function("Sqrt", &Math::Sqrt);
	math_table.set_function("InvSqrt", &Math::InvSqrt);
	math_table.set_function("RealEqual", &Math::RealEqual);
	math_table.set_function("Clamp", &Math::Clamp);
	math_table.set_function("GetMaxElement", &Math::GetMaxElement);

	math_table.set_function("DegreesToRadians", &Math::DegreesToRadians);
	math_table.set_function("RadiansToDegrees", &Math::RadiansToDegrees);
	math_table.set_function("AngleUnitsToRadians", &Math::AngleUnitsToRadians);
	math_table.set_function("RadiansToAngleUnits", &Math::RadiansToAngleUnits);
	math_table.set_function("AngleUnitsToDegrees", &Math::AngleUnitsToDegrees);
	math_table.set_function("DegreesToAngleUnits", &Math::DegreesToAngleUnits);

	math_table.set_function("Sin", (float(*)(float))&Math::Sin);
	math_table.set_function("Cos", (float(*)(float))&Math::Cos);
	math_table.set_function("Tan", (float(*)(float))&Math::Tan);
	math_table.set_function("Acos", &Math::Acos);
	math_table.set_function("Asin", &Math::Asin);
	math_table.set_function("Atan", &Math::Atan);
	math_table.set_function("Atan2", &Math::Atan2);

	sol::usertype<Radian> type_radian = math_table.new_usertype<Radian>
	(
		"Radian",
		sol::constructors<Radian(float), Radian(const Degree&)>(),
		"ValueRadians", &Radian::ValueRadians,
		"ValueDegrees", &Radian::ValueDegrees,
		"ValueAngleUnits", &Radian::ValueAngleUnits,
		"SetValue", &Radian::SetValue
	);

	sol::usertype<Degree> type_degree = math_table.new_usertype<Degree>
	(
		"Degree",
		sol::constructors<Degree(float), Degree(const Radian&)>(),
		"ValueDegrees", &Degree::ValueDegrees,
		"ValueRadians", &Degree::ValueRadians,
		"ValueAngleUnits", &Degree::ValueAngleUnits
	);


	sol::usertype<Vector3> type_vector3 = math_table.new_usertype<Vector3>
	(
		"Vector3",
		sol::constructors<Vector3(), Vector3(float), Vector3(float, float, float), Vector3(Vector4)>(),
		"x", &Vector3::x,
		"y", &Vector3::y,
		"z", &Vector3::z,
		sol::meta_function::addition, sol::overload(
			[](const Vector3& lhs, const Vector3& rhs) { return lhs + rhs; },
			[](float lhs, const Vector3& rhs) { return lhs + rhs; },
			[](const Vector3& lhs, float rhs) { return lhs + rhs; }
		),
		sol::meta_function::subtraction, sol::overload(
			[](const Vector3& lhs, const Vector3& rhs) { return lhs - rhs; },
			[](float lhs, const Vector3& rhs) { return lhs - rhs; },
			[](const Vector3& lhs, float rhs) { return lhs - rhs; }
		),
		sol::meta_function::multiplication, sol::overload(
			[](const Vector3& lhs, const Vector3& rhs) { return lhs * rhs; },
			[](float lhs, const Vector3& rhs) { return lhs * rhs; },
			[](const Vector3& lhs, float rhs) { return lhs * rhs; }
		),
		sol::meta_function::division, sol::overload(
			[](const Vector3& lhs, const Vector3& rhs) { return lhs / rhs; },
			[](float lhs, const Vector3& rhs) { return lhs / rhs; },
			[](const Vector3& lhs, float rhs) { return lhs / rhs; }
		),
		sol::meta_function::equal_to, [](const Vector3& lhs, const Vector3& rhs) { return lhs == rhs; },
		sol::meta_function::unary_minus, [](const Vector3& v) { return -v; },
		sol::meta_function::to_string, [](const Vector3& v) { return "x:" + to_string(v.x) + ", y:" + to_string(v.y) + ", z:" + to_string(v.z); },
		"Length", &Vector3::Length,
		"SquaredLength", &Vector3::SquaredLength,
		"AbsoluteCopy", &Vector3::AbsoluteCopy,
		"AngleBetween", &Vector3::AngleBetween,
		"Cross", &Vector3::CrossProduct,
		"Dot", &Vector3::DotProduct,
		"Distance", &Vector3::Distance,
		"SquaredDistance", &Vector3::SquaredDistance,
		"Normalise", &Vector3::Normalise,
		"NormalisedCopy", &Vector3::NormalisedCopy,
		"MakeFloor", &Vector3::MakeFloor,
		"MakeCeil", &Vector3::MakeCeil,
		"IsZeroLength", &Vector3::IsZeroLength,
		"IsZero", &Vector3::IsZero,
		"Reflect", &Vector3::Reflect,
		"Project", &Vector3::Project,
		"Clamp", & Vector3::Clamp,
		"Lerp", &Vector3::Lerp,
		"GetMaxElement", &Vector3::GetMaxElement,
		"IsNaN", &Vector3::IsNaN
	);
	sol::usertype<Vector4> type_vector4 = math_table.new_usertype<Vector4>
	(
		"Vector4",
		sol::constructors<Vector4(), Vector4(float, float, float, float), Vector4(Vector3, float)>(),
		"x", &Vector4::x,
		"y", &Vector4::y,
		"z", &Vector4::z,
		"w", &Vector4::w,
		sol::meta_function::addition, sol::overload(
			[](const Vector4& lhs, const Vector4& rhs) { return lhs + rhs; },
			[](float lhs, const Vector4& rhs) { return lhs + rhs; },
			[](const Vector4& lhs, float rhs) { return lhs + rhs; }
		),
		sol::meta_function::subtraction, sol::overload(
			[](const Vector4& lhs, const Vector4& rhs) { return lhs - rhs; },
			[](float lhs, const Vector4& rhs) { return lhs - rhs; },
			[](const Vector4& lhs, float rhs) { return lhs - rhs; }
		),
		sol::meta_function::multiplication, sol::overload(
			[](const Vector4& lhs, const Vector4& rhs) { return lhs * rhs; },
			[](float lhs, const Vector4& rhs) { return lhs * rhs; },
			[](const Vector4& lhs, float rhs) { return lhs * rhs; }
		),
		sol::meta_function::division, sol::overload(
			[](const Vector4& lhs, const Vector4& rhs) { return lhs / rhs; },
			[](float lhs, const Vector4& rhs) { return lhs / rhs; },
			[](const Vector4& lhs, float rhs) { return lhs / rhs; }
		),
		sol::meta_function::equal_to, [](const Vector4& lhs, const Vector4& rhs) { return lhs == rhs; },
		sol::meta_function::unary_minus, [](const Vector4& v) { return -v; },
		sol::meta_function::to_string, [](const Vector4& v) { return "x:"+to_string(v.x)+", y:"+to_string(v.y)+", z:"+to_string(v.z)+", w:"+to_string(v.w); },
		"DotProduct", & Vector4::DotProduct,
		"IsNaN", & Vector4::IsNaN
	);

	{
		sol::table package_table = lua["package"];
		std::string path = package_table["path"];
		path.append(";C:/Users/asus/Desktop/Example/lua_code/?.lua;");
		package_table["path"] = path;
	}

	lua.script_file("C:\\Users\\asus\\Desktop\\Example\\lua_code\\main.lua");

	

	return 0;
}