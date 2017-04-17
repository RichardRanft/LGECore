#include "stdafx.h"
#include "RegisterLunaClasses.h"

int main(int argc, char* argv[]) {
	lua_State* state = luaL_newstate();
	luaL_openlibs(state);

	registerLuaClasses(state);

	CApp theApp(state, 1024, 600);

	int ret = theApp.OnExecute();

	lua_close(state);

	return ret;
}