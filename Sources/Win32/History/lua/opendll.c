#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <windows.h>
static int MyLuaDLL_HelloWorld(lua_State* L)
{
	MessageBox(NULL,"Hello","World",MB_OK);
	return 0;
}
static int MyLuaDLL_average(lua_State *L)
{
	int n = lua_gettop(L);
	double sum = 0;
	int i;
	for (i = 1; i <= n; i++) {
		sum += lua_tonumber(L, i);
	}
	lua_pushnumber(L, sum / n);
	lua_pushnumber(L, sum);
	return 2;
}
static const luaL_Reg MyLuaDLLFunctions [] = {
	{"HelloWorld",MyLuaDLL_HelloWorld},
	{"average",MyLuaDLL_average},
	{NULL, NULL}
};
int __cdecl __declspec(dllexport) luaopen_MyLuaDLL(lua_State* L)
{
	//luaL_openlib(L, "MyLuaDLL", MyLuaDLLFunctions, 0);
	lua_getglobal(L, "MyLuaDLL");
	if (lua_isnil(L, -1)) {
		lua_pop(L, 1);
		lua_newtable(L);
	}
	luaL_setfuncs(L, MyLuaDLLFunctions, 0);
	lua_setglobal(L, "MyLuaDLL");
	return 1;
}