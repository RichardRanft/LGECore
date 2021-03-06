#pragma once
#ifndef _CSURFACE_H_
#define _CSURFACE_H_

#include "stdafx.h"
#include <SDL_image.h>

class CSurface {
private:
	lua_State* m_state;

public:
	CSurface();
	CSurface(lua_State* L);
	~CSurface();

	static SDL_Surface* OnLoad(char* File);
	static SDL_Surface* OnLoad(char* File, const SDL_Surface& Surf_Dest);
	static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y);
	static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H);
	static SDL_Surface* ScaleSurface(SDL_Surface* Surface, Uint16 Width, Uint16 Height);

	static const char *className;
	static const Luna <CSurface>::FunctionType methods[];
	static const Luna <CSurface>::PropertyType properties[];

	bool isExisting; // This is used by Luna to see whether it's been created by createFromExisting.  Don't set it.
	bool isPrecious; // This is used to tell Luna not to garbage collect the object, in case other objects might reference it.  Set it in your class's constructor.

	// Lua interface
	int setTarget(lua_State* L);
	int getTarget(lua_State* L);
	int setScale(lua_State* L);
	int getScale(lua_State* L);
	int setPosition(lua_State* L);
	int getPosition(lua_State* L);
};

#endif