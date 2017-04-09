#include "stdafx.h"
#include "LGECore.h"

void registerLuaClasses(lua_State* state)
{
	Luna<CApp>::Register(state);
}


int main(int argc, char* argv[]) {
	lua_State* state = luaL_newstate();
	luaL_openlibs(state);

	registerLuaClasses(state);

	CApp theApp(state, 1024, 600);

	return theApp.OnExecute();
}