#include "stdafx.h"
#include "CApp.h"
#include "CEvent.h"
#include "CGuiBase.h"
#include "CImageResource.h"
#include "CResourceInstance.h"
#include "CResourceManager.h"
#include "CSound.h"
#include "CSoundResource.h"
#include "CSurface.h"

void registerLuaClasses(lua_State* state)
{
	Luna<CApp>::Register(state);
	Luna<CEvent>::Register(state);
	Luna<CGuiBase>::Register(state);
	Luna<CImageResource>::Register(state);
	Luna<CResourceInstance>::Register(state);
	Luna<CResourceManager>::Register(state);
	Luna<CSound>::Register(state);
	Luna<CSoundResource>::Register(state);
	Luna<CSurface>::Register(state);
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