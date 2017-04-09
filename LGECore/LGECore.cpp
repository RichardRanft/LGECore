// LGECore.cpp : Defines the entry point for the console application.
//

#include "LGECore.h"
#include "CSurface.h"
#include "CEvent.h"

CApp::CApp() {
	m_running = true;
	m_state = luaL_newstate();
	m_screen_width = 1024;
	m_screen_height = 600;
	appName = "LGECore Application";
}

CApp::CApp(lua_State* l, int width, int height) {
	m_running = true;
	m_state = l;
	m_screen_width = width;
	m_screen_height = height;
	appName = "LGECore Application";
}

CApp::~CApp()
{
	if (m_state != nullptr)
	{
		lua_close(m_state);
		m_state = nullptr;
	}
}

int CApp::OnExecute() {
	if (OnInit() == false) {
		return -1;
	}

	SDL_Event Event;

	while (m_running) {
		while (SDL_PollEvent(&Event)) {
			OnEvent(&Event);
		}

		OnLoop();
		OnRender();
	}

	OnCleanup();

	return 0;
}

bool CApp::OnInit() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "SDL video init failed: %s\n", SDL_GetError());
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0)
	{
		fprintf(stderr, "SDL2_image init failed: %s\n", SDL_GetError());
		return false;
	}

	m_window = SDL_CreateWindow(appName.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		m_screen_width, m_screen_height, SDL_WINDOW_SHOWN);

	if (m_window == NULL) {
		fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
		return false;
	}

	m_screenSurface = SDL_GetWindowSurface(m_window);

	if (!m_screenSurface) {
		fprintf(stderr, "Screen surface could not be created: %s\n", SDL_GetError());
		SDL_Quit();
		return false;
	}

	m_defaultSurface = CSurface::OnLoad("defaultbackground.png", (const SDL_Surface &)*m_screenSurface);

	if (!m_defaultSurface) {
		fprintf(stderr, "Default background could not be loaded: %s\n", SDL_GetError());
		SDL_Quit();
		return false;
	}

	m_defaultSurface = CSurface::ScaleSurface(m_defaultSurface, m_screen_width, m_screen_height);

	return true;
}

void CApp::OnEvent(SDL_Event* Event)
{
	CEvent::OnEvent(Event);
}

void CApp::OnExit()
{
	m_running = false;
}

void CApp::OnLoop() {
}

void CApp::OnRender() {
	CSurface::OnDraw(m_screenSurface, m_defaultSurface, 0, 0, 0, 0, m_screen_width, m_screen_height);
	SDL_UpdateWindowSurface(m_window);
}

void CApp::OnCleanup() {
	SDL_FreeSurface(m_screenSurface);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}


// Lua interface implementation
const char *CApp::className = "CApp";
const Luna < CApp >::FunctionType CApp::methods[] = {
	//{ "getInput", &CApp::getInput },
	{ 0 }
};

const Luna < CApp >::PropertyType CApp::properties[] = {
	{ 0 }
};
