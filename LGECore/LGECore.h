#pragma once
#ifndef _CAPP_H_
#define _CAPP_H_

#include <SDL.h>
#include <string>
#include "luna.h"
#include "CEvent.h"
#include "CSurface.h"

class CApp : public CEvent 
{
	private:
		lua_State *m_state;
		bool m_running;
		int m_screen_width;
		int m_screen_height;
		SDL_Window* m_window = NULL;
		SDL_Surface* m_screenSurface = NULL;
		SDL_Surface* m_defaultSurface = NULL;

		std::string appName;

	public:

		CApp();
		CApp(lua_State *l, int width, int height);
		~CApp();

		int OnExecute();
		bool OnInit();
		void OnEvent(SDL_Event* Event);
		void OnLoop();
		void OnRender();
		void OnCleanup();
		void OnExit();

		static const char *className;
		static const Luna <CApp>::FunctionType methods[];
		static const Luna <CApp>::PropertyType properties[];

		bool isExisting; // This is used by Luna to see whether it's been created by createFromExisting.  Don't set it.
		bool isPrecious; // This is used to tell Luna not to garbage collect the object, in case other objects might reference it.  Set it in your class's constructor.

		// Lua interface

};

#endif