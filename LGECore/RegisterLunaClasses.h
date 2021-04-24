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
