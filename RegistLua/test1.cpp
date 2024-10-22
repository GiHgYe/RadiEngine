#include <iostream>
extern "C" 
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "lstate.h"
}

using namespace std;

class A
{
public:
	A(const string& name) : name(name) {}
	~A() { cout << "Destruct A\n"; }
	void SetName(const string& name) { this->name = name; }
	string GetName() const { return name; }
	void Print() const { cout << name << endl; }
	string name;
};

static int Create_A(lua_State* L) {
	A** a = (A**)lua_newuserdata(L, sizeof(A*));
	*a = new A{""};

	luaL_getmetatable(L, "AClass");
	lua_setmetatable(L, -2);
	return 1;
}
static int Set_A_Name(lua_State* L) {
	A** a = (A**)luaL_checkudata(L, 1, "AClass");
	luaL_argcheck(L, a != NULL, 1, "invalid user data");

	luaL_checktype(L, -1, LUA_TSTRING);
	(*a)->SetName(lua_tostring(L, -1));
	return 0;
}
static int Get_A_Name(lua_State* L) {
	A** a = (A**)luaL_checkudata(L, 1, "AClass");
	luaL_argcheck(L, a != NULL, 1, "invalid user data");

	lua_pushstring(L, (*a)->GetName().c_str());
	return 1;
}
static int Print_A(lua_State* L) {
	A** a = (A**)luaL_checkudata(L, 1, "AClass");
	luaL_argcheck(L, a != NULL, 1, "invalid user data");

	(*a)->Print();
	lua_pushstring(L, (*a)->name.c_str());
	return 1;
}

static int Auto_Gc(lua_State* L) {
	A** a = (A**)luaL_checkudata(L, 1, "AClass");
	luaL_argcheck(L, a != NULL, 1, "invalid user data");

	if (a) delete* a;
	return 0;
}

static const luaL_Reg reg_A_constructor_funcs[] = {
	{"create", Create_A},
	{NULL, NULL}
};

static const luaL_Reg reg_A_member_funcs[] = {
	{"set_name", Set_A_Name},
	{"get_name", Get_A_Name},
	{"__tostring", Print_A},
	{"__gc", Auto_Gc},
	{NULL, NULL}
};

static int lua_open_A_libs(lua_State* L) {
	cout << lua_gettop(L) << endl;
	luaL_newmetatable(L, "AClass");
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, reg_A_member_funcs, 0);

	luaL_newlib(L, reg_A_constructor_funcs);
	return 1;
}

static const luaL_Reg lua_reg_libs[] = {
	{"A", lua_open_A_libs},
	{NULL, NULL}
};

int test1()
{
	lua_State* L = luaL_newstate();
	if (L == NULL) return -1;

	luaL_openlibs(L);
	for (const luaL_Reg* lua_reg = lua_reg_libs; lua_reg->func; ++lua_reg)
	{
		luaL_requiref(L, lua_reg->name, lua_reg->func, 1);
		lua_pop(L, 1);
	}

	if (luaL_dofile(L, "C:\\Users\\asus\\Desktop\\Example\\lua_code\\test.lua"))
	{
		cout << lua_tostring(L, -1) << endl;
	}

	lua_close(L);

	return 0;
}