#pragma once
#ifndef _CEVENT_H_
#define _CEVENT_H_

#include <SDL.h>
#include <stdarg.h>
#include <cstdio>
#include <varargs.h>

#include "luna.h"

class CEvent {
private:
	lua_State* m_state;

protected:
	int error(const char* msg, ...);

public:
	CEvent();
	CEvent(lua_State* L);
	virtual ~CEvent();

	virtual void OnEvent(SDL_Event* Event);
	virtual void OnExit();
	virtual void OnKeyDown(SDL_Keycode sym, Uint16 mod, Uint16 scancode);
	virtual void OnKeyUp(SDL_Keycode sym, Uint16 mod, Uint16 scancode);
	virtual void OnMouseMove(int mx, int my, int relx, int rely, bool Left, bool Right, bool Middle);
	virtual void OnLButtonDown(int mx, int my);
	virtual void OnLButtonUp(int mx, int my);
	virtual void OnRButtonDown(int mx, int my);
	virtual void OnRButtonUp(int mx, int my);
	virtual void OnMButtonDown(int mx, int my);
	virtual void OnMButtonUp(int mx, int my);
	virtual void OnMouseFocus();
	virtual void OnMouseBlur();
	virtual void OnInputFocus();
	virtual void OnInputBlur();
	virtual void OnWindowResized(int data1, int data2);
	virtual void OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value);
	virtual void OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel);
	virtual void OnJoyHat(Uint8 which, Uint8 hat, Uint8 button);
	virtual void OnJoyButtonDown(Uint8 which, Uint8 button);
	virtual void OnJoyButtonUp(Uint8 which, Uint8 button);
	virtual void OnUser(Uint8 type, int code, void* data1, void* data2);
	virtual void CallLuaFunction(const char* funcName, const char* funcSig, ...);

	static const char *className;
	static const Luna <CEvent>::FunctionType methods[];
	static const Luna <CEvent>::PropertyType properties[];

	bool isExisting; // This is used by Luna to see whether it's been created by createFromExisting.  Don't set it.
	bool isPrecious; // This is used to tell Luna not to garbage collect the object, in case other objects might reference it.  Set it in your class's constructor.

	// Lua interface
	//int getName(lua_State* L);
};

#endif