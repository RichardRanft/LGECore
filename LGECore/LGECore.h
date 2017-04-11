#pragma once
#ifndef _CAPP_H_
#define _CAPP_H_

#include <SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include "CDebugOutput.h"
#include "luna.h"
#include "CEvent.h"
#include "CSurface.h"

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

		std::string appName;

		std::string m_backgroundName;

		bool runScript(lua_State* L, std::string filename);
		bool runScript(lua_State* L, int argCount, const char** args);
		bool loadScripts(lua_State* L);
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

		static const char *className;
		static const Luna <CApp>::FunctionType methods[];
		static const Luna <CApp>::PropertyType properties[];

		bool isExisting; // This is used by Luna to see whether it's been created by createFromExisting.  Don't set it.
		bool isPrecious; // This is used to tell Luna not to garbage collect the object, in case other objects might reference it.  Set it in your class's constructor.

		// Lua interface
		//int getInput(lua_State* L);
		int setAppName(lua_State* L);
		int setResolution(lua_State* L);
		int getResolution(lua_State* L);
		int setBackground(lua_State* L);
		int getBackground(lua_State* L);

};

#endif