#include "stdafx.h"
#include "LGECore.h"
#include "CSurface.h"
#include "CSound.h"
#include "CImageResource.h"
#include "CSoundResource.h"

void registerLuaClasses(lua_State* state)
{
	Luna<CApp>::Register(state);
	Luna<CSound>::Register(state);
	Luna<CSurface>::Register(state);
	Luna<CSoundResource>::Register(state);
	Luna<CImageResource>::Register(state);
}


int main(int argc, char* argv[]) {
	lua_State* state = luaL_newstate();
	luaL_openlibs(state);

	registerLuaClasses(state);

	CApp theApp(state, 1024, 600);

	int ret = theApp.OnExecute();

	lua_close(state);

	return ret;
}