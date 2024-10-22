#pragma once
#include "meta/reflection/reflection.h"
#include "meta/json.h"
#include <cassert>

template<typename...>
inline constexpr bool always_false = false;

class Serializer
{
public:
	template<typename T>
	static Json WritePoint(T* instance) {
		return Json::object{ {"$typeName", "*"}, {"$context", Serializer::Write(*instance) } };
	}

	template<typename T>
	static T*& ReadPoint(const Json& json_context, T*& instance)
	{
		assert(instance == nullptr);
		std::string typeName = json_context["$typeName"].string_value();
		assert(!typeName.empty());
		if (typeName[0] == '*')
		{
			instance = new T;
			Read(json_context["$context"], *instance);
		}
		else
		{
			instance = static_cast<T*>(Reflection::TypeMeta::newFromNameAndJson(typeName, json_context["$context"]).m_instance);
		}
		return instance;
	}

	template<typename T>
	static Json Write(const Reflection::ReflectionPtr<T>& instance)
	{
		T* instance_ptr = static_cast<T*>(instance.operator->());
		std::string type_name = instance.getTypeName();
		return Json::object{ {"$typeName", Json(type_name)},
							 {"$context", Reflection::TypeMeta::writeByName(type_name, instance_ptr)} };
	}

	template<typename T>
	static T*& Read(const Json& json_context, Reflection::ReflectionPtr<T>& instance)
	{
		std::string type_name = json_context["$typeName"].string_value();
		instance.setTypeName(type_name);
		return ReadPoint(json_context, instance.getPtrReference());
	}

	template<typename T>
	static Json Write(const T& instance)
	{
		if constexpr (std::is_pointer<T>::value) {
			return WritePoint((T)instance);
		}
		else {
			static_assert(always_false<T>, "Serializer::Write<T> has not been implemented yet!");
			return Json();
		}
	}

	template<typename T>
	static T& Read(const Json& json_context, T& instance) {
		if constexpr (std::is_pointer<T>::value) {
			return ReadPoint(json_context, instance);
		}
		else {
			static_assert(always_false<T>, "Serializer::Read<T> has not been implemented yet!");
			return instance;
		}
	}
};

template<>
Json Serializer::Write(const char& instance);
template<>
char& Serializer::Read(const Json& json_context, char& instance);

template<>
Json Serializer::Write(const int& instance);
template<>
int& Serializer::Read(const Json& json_context, int& instance);

template<>
Json Serializer::Write(const unsigned int& instance);
template<>
unsigned int& Serializer::Read(const Json& json_context, unsigned int& instance);

template<>
Json Serializer::Write(const float& instance);
template<>
float& Serializer::Read(const Json& json_context, float& instance);

template<>
Json Serializer::Write(const double& instance);
template<>
double& Serializer::Read(const Json& json_context, double& instance);

template<>
Json Serializer::Write(const bool& instance);
template<>
bool& Serializer::Read(const Json& json_context, bool& instance);

template<>
Json Serializer::Write(const std::string& instance);
template<>
std::string& Serializer::Read(const Json& json_context, std::string& instance);
