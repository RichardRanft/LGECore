#pragma once
#include "luna.h"
#include <SDL.h>
#include <SDL_mixer.h>

class CSound 
{
public:
	CSound();
	CSound(lua_State* L);
	~CSound();

	static const char *className;
	static const Luna <CSound>::FunctionType methods[];
	static const Luna <CSound>::PropertyType properties[];

	bool isExisting; // This is used by Luna to see whether it's been created by createFromExisting.  Don't set it.
	bool isPrecious; // This is used to tell Luna not to garbage collect the object, in case other objects might reference it.  Set it in your class's constructor.

	// Lua interface
	int getName(lua_State* L);
	int play(lua_State* L);
	int stop(lua_State* L);
	int setChannel(lua_State* L);
	int getChannel(lua_State* L);
	int setVolume(lua_State* L);
	int getVolume(lua_State* L);
};