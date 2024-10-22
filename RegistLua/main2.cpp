#include <iostream>
#define SOL_ALL_SAFETIES_ON 1
#include "sol/sol.hpp"

using namespace std;

#ifndef EXAMPLES_ASSERT_HPP
#define EXAMPLES_ASSERT_HPP
#   define m_assert(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)

#   define c_assert(condition) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
#   define m_assert(condition, message) do { if (false) { (void)(condition); (void)sizeof(message); } } while (false)
#   define c_assert(condition) do { if (false) { (void)(condition); } } while (false)
#endif


struct Doge {
	int tailwag = 50;
	Doge() {
		std::cout << "Dog at " << this << " is being create..." << std::endl;
	}
	Doge(int wags)
		: tailwag(wags) {
		std::cout << "Dog at " << this << " is being create..." << std::endl;
	}
	~Doge() {
		std::cout << "Dog at " << this << " is being destroyed..." << std::endl;
	}
};


int test2()
{
	sol::state lua;
	lua.open_libraries();
	/*lua.new_usertype<Vec2>("Vec2",
		sol::constructors<sol::types<float>, sol::types<float>>(),
		"toString", &Vec2::toString);*/

	//lua.script("local vec2 = Vec2.new(); vec2:toString();");

	//auto script1 = lua1.load("a = 'test'; return 15;");
	//auto res1 = script1();
	//if (res1.valid()) {
	//	cout << res1.get<int>() << endl;
	//}

	//const auto& my_script = R"(
	//	local a,b,c = ...
	//	print(a,b,c)
	//)";
	//
	//sol::load_result fx = lua1.load(my_script);
	//if (!fx.valid()) {
	//	sol::error err = fx;
	//	std::cerr << "failed to load string-based script into the program" << err.what() << std::endl;
	//}
	//fx("your", "arguments", "here");

	lua.set("number", 24, "number2", 25.5, "number3", 26);
	lua["important_string"] = "this is a string";
	lua["a_function"] = [](int a, int b) { return a + b; };
	lua["some_table"] = lua.create_table_with("value", 24, "str", "table string");
	std::string equivalent_code = R"(
		t = {
			number = 24,
			number2 = 25.5,
			important_string = "woof woof",
			a_function = function () return 100 end,
			some_table = { value = 24 }
		}
	)";
	lua.script(equivalent_code);
	sol::function a_function = lua["a_function"];
	std::function<int(int, int)> a_std_function = a_function;
	cout << a_std_function(1, 2) << endl;
	int i = a_function(3, 4);
	cout << i << endl;

	sol::object number_obj = lua.get<sol::object>("number");
	sol::type t1 = number_obj.get_type();
	c_assert(t1 == sol::type::number);

	Doge dog{ 30 };
	// fresh one put into Lua
	lua["dog"] = Doge{};

	// Copy into lua: destroyed by Lua VM during garbage collection
	lua["dog_copy"] = dog;
	// OR: move semantics - will call move constructor if present instead
	// Again, owned by Lua
	lua["dog_move"] = std::move(dog);
	lua["dog_unique_ptr"] = std::make_unique<Doge>(25);
	lua["dog_shared_ptr"] = std::make_shared<Doge>(31);

	// Identical to above
	Doge dog2{ 30 };
	lua.set("dog2", Doge{});
	lua.set("dog2_copy", dog2);
	lua.set("dog2_move", std::move(dog2));
	lua.set("dog2_unique_ptr", std::unique_ptr<Doge>(new Doge(25)));
	lua.set("dog2_shared_ptr", std::shared_ptr<Doge>(new Doge(31)));

	// Note all of them can be retrieved the same way:
	Doge& lua_dog = lua["dog"];
	Doge& lua_dog_copy = lua["dog_copy"];
	Doge& lua_dog_move = lua["dog_move"];
	Doge& lua_dog_unique_ptr = lua["dog_unique_ptr"];
	Doge& lua_dog_shared_ptr = lua["dog_shared_ptr"];
	c_assert(lua_dog.tailwag == 50);
	c_assert(lua_dog_copy.tailwag == 30);
	c_assert(lua_dog_move.tailwag == 30);
	c_assert(lua_dog_unique_ptr.tailwag == 25);
	c_assert(lua_dog_shared_ptr.tailwag == 31);
	std::cout << std::endl;
	lua["dog3"] = &dog;
	// Same as above: respects std::reference_wrapper
	lua["dog_ref"] = std::ref(dog);
	// These two are identical to above
	//lua.set("dog", &dog);
	//lua.set("dog", std::ref(dog));
	

	std::cout << "=== dump (serialize between states) ===" << std::endl;

	sol::state lua2;

	lua2.open_libraries(sol::lib::base);

	sol::load_result lr = lua.load("a = function (v) print(v) return v end");
	c_assert(lr.valid());

	sol::protected_function target = lr.get<sol::protected_function>();
	sol::bytecode target_bc = target.dump();

	auto result2 = lua2.safe_script(target_bc.as_string_view(), sol::script_pass_on_error);
	c_assert(result2.valid());

	sol::protected_function pf = lua2["a"];
	int v = pf(25557);
	c_assert(v == 25557);

	return 0;
}