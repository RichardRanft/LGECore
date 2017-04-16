#pragma once
#include <SDL.h>
#include <string>

#include "luna.h"
#include "CEvent.h"

class CGuiBase : public CEvent
{
private:
	lua_State* m_state;
public:
	CGuiBase();
	CGuiBase(lua_State* l);
	~CGuiBase();

	std::string Name;

	void OnEvent(SDL_Event* event);

	static const char *className;
	static const Luna <CGuiBase>::FunctionType methods[];
	static const Luna <CGuiBase>::PropertyType properties[];

	bool isExisting; // This is used by Luna to see whether it's been created by createFromExisting.  Don't set it.
	bool isPrecious; // This is used to tell Luna not to garbage collect the object, in case other objects might reference it.  Set it in your class's constructor.

	// Lua interface
	int setName(lua_State* L);
	int getName(lua_State* L);
};