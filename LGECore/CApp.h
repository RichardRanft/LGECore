#pragma once
#ifndef _CAPP_H_
#define _CAPP_H_

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include "CDebugOutput.h"
#include "CEvent.h"
#include "CSurface.h"
#include "CResourceManager.h"

class CApp : public CEvent
{
	private:
		lua_State *m_state;
		CDebugOutput* m_debugOut;

		bool m_running;
		int m_screen_width;
		int m_screen_height;
		SDL_Window* m_window = NULL;
		SDL_Surface* m_screenSurface = NULL;
		SDL_Surface* m_defaultSurface = NULL;
		CResourceManager m_resman;

		std::string appName;

		std::string m_backgroundName;

		void registerThis();
		bool runScript(std::string filename);
		bool runScript(int argCount, const char** args);
		bool loadScripts();
		void getScriptFileName(char* str, std::string& dest, const char* delim);
		bool getFileList(std::string *dirName, std::vector<std::string*>* target);

	public:

		CApp(lua_State *l);
		CApp(lua_State *l, int width, int height);
		~CApp();

		int OnExecute();
		bool OnInit();
		void OnEvent(SDL_Event* event);
		void OnLoop();
		void OnRender();
		void OnCleanup();
		void OnExit();

		void OnKeyDown(SDL_Keycode sym, Uint16 mod, Uint16 scancode);
		void OnKeyUp(SDL_Keycode sym, Uint16 mod, Uint16 scancode);


		static const char *className;
		static const Luna <CApp>::FunctionType methods[];
		static const Luna <CApp>::PropertyType properties[];

		bool isExisting; // This is used by Luna to see whether it's been created by createFromExisting.  Don't set it.
		bool isPrecious; // This is used to tell Luna not to garbage collect the object, in case other objects might reference it.  Set it in your class's constructor.

		// Lua interface
		int run(lua_State* L);
		int setAppName(lua_State* L);
		int setResolution(lua_State* L);
		int getResolution(lua_State* L);
		int setBackground(lua_State* L);
		int getBackground(lua_State* L);

};

#endif