// LGECore.cpp : Defines the entry point for the console application.
//
#include "LGECore.h"
#include "CSurface.h"
#include "CEvent.h"
#include "CDebugOutput.h"

CApp::CApp(lua_State *l) {
	m_debugOut = new CDebugOutput();
	m_running = true;
	m_state = l;
	m_screen_width = 1024;
	m_screen_height = 600;
	m_backgroundName = "defaultbackground.png";
	m_resman = CResourceManager(m_state);
	appName = "LGECore Application";
}

CApp::CApp(lua_State* l, int width, int height) {
	m_debugOut = new CDebugOutput();
	m_running = true;
	m_state = l;
	m_screen_width = width;
	m_screen_height = height;
	m_backgroundName = "defaultbackground.png";
	m_resman = CResourceManager(m_state);
	appName = "LGECore Application";
}

CApp::~CApp()
{
	m_resman.Clear();
	if (m_state != nullptr)
	{
		m_state = nullptr;
	}
}

int CApp::OnExecute() {
	m_debugOut->outputDebugString(1, " -- Loading...\n");
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
	m_debugOut->outputDebugString(1, " -- Initializing SDL...\n");
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

	if (Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3) < 0)
	{
		fprintf(stderr, "SDL2_mixer init failed: %s\n", SDL_GetError());
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

	m_defaultSurface = CSurface::OnLoad((char*)m_backgroundName.c_str(), (const SDL_Surface &)*m_screenSurface);

	if (!m_defaultSurface) {
		fprintf(stderr, "Default background could not be loaded: %s\n", SDL_GetError());
		SDL_Quit();
		return false;
	}

	m_defaultSurface = CSurface::ScaleSurface(m_defaultSurface, m_screen_width, m_screen_height);

	loadScripts();

	return true;
}

void CApp::OnEvent(SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_WINDOWEVENT:
	{
		switch (event->window.event)
		{
		case SDL_WINDOWEVENT_ENTER:
		{
			OnMouseFocus();
			break;
		}
		case SDL_WINDOWEVENT_LEAVE:
		{
			OnMouseBlur();
			break;
		}
		case SDL_WINDOWEVENT_FOCUS_GAINED:
		{
			OnInputFocus();
			break;
		}
		case SDL_WINDOWEVENT_FOCUS_LOST:
		{
			OnInputBlur();
			break;
		}
		case SDL_WINDOWEVENT_SHOWN:
		{
			break;
		}
		case SDL_WINDOWEVENT_HIDDEN:
		{
			break;
		}
		case SDL_WINDOWEVENT_EXPOSED:
		{
			break;
		}
		case SDL_WINDOWEVENT_MOVED:
		{
			break;
		}
		case SDL_WINDOWEVENT_RESIZED:
		{
			OnWindowResized(event->window.data1, event->window.data2);
			break;
		}
		case SDL_WINDOWEVENT_SIZE_CHANGED:
		{
			break;
		}
		case SDL_WINDOWEVENT_MINIMIZED:
		{
			break;
		}
		case SDL_WINDOWEVENT_MAXIMIZED:
		{
			break;
		}
		case SDL_WINDOWEVENT_RESTORED:
		{
			break;
		}
		case SDL_WINDOWEVENT_CLOSE:
		{
			break;
		}
		}
		break;
	}
	case SDL_QUIT:
	{
		OnExit();
		break;
	}
	case SDL_KEYDOWN:
	{
		OnKeyDown(event->key.keysym.sym, event->key.keysym.mod, event->key.keysym.scancode);
		break;
	}
	case SDL_KEYUP:
	{
		OnKeyUp(event->key.keysym.sym, event->key.keysym.mod, event->key.keysym.scancode);
		break;
	}
	case SDL_MOUSEMOTION:
	{
		OnMouseMove(event->motion.x, event->motion.y, event->motion.xrel, event->motion.yrel, (event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT)) != 0, (event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0, (event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);
		break;
	}
	case SDL_MOUSEBUTTONDOWN:
	{
		switch (event->button.button)
		{
		case SDL_BUTTON_LEFT:
		{
			OnLButtonDown(event->button.x, event->button.y);
			break;
		}
		case SDL_BUTTON_RIGHT:
		{
			OnRButtonDown(event->button.x, event->button.y);
			break;
		}
		case SDL_BUTTON_MIDDLE:
		{
			OnMButtonDown(event->button.x, event->button.y);
			break;
		}
		}
		break;
	}

	case SDL_MOUSEBUTTONUP:
	{
		switch (event->button.button)
		{
		case SDL_BUTTON_LEFT:
		{
			OnLButtonUp(event->button.x, event->button.y);
			break;
		}
		case SDL_BUTTON_RIGHT:
		{
			OnRButtonUp(event->button.x, event->button.y);
			break;
		}
		case SDL_BUTTON_MIDDLE:
		{
			OnMButtonUp(event->button.x, event->button.y);
			break;
		}
		}
		break;
	}

	//Star getting things from here man!
	case SDL_JOYAXISMOTION:
	{
		OnJoyAxis(event->jaxis.which, event->jaxis.axis, event->jaxis.value);
		break;
	}
	case SDL_JOYBALLMOTION:
	{
		OnJoyBall(event->jball.which, event->jball.ball, event->jball.xrel, event->jball.yrel);
		break;
	}
	case SDL_JOYHATMOTION:
	{
		OnJoyHat(event->jhat.which, event->jhat.hat, event->jhat.value);
		break;
	}
	case SDL_JOYBUTTONDOWN:
	{
		OnJoyButtonDown(event->jbutton.which, event->jbutton.button);
		break;
	}
	case SDL_JOYBUTTONUP:
	{
		OnJoyButtonUp(event->jbutton.which, event->jbutton.button);
		break;
	}
	default:
	{
		OnUser(event->user.type, event->user.code, event->user.data1, event->user.data2);
		break;
	}
	}
}

void CApp::OnKeyDown(SDL_Keycode sym, Uint16 mod, Uint16 scancode)
{
	if (m_state != nullptr)
	{
		// try to call Lua callback
	}
	printf("keycode:%d\tmod:%d\tscancode:%d pressed.\n", sym, mod, scancode);
	//keycode:27      mod:4096        scancode:41 pressed.
	if (sym == 27 && mod == 4096 && scancode == 41)
		m_running = false;
}

void CApp::OnKeyUp(SDL_Keycode sym, Uint16 mod, Uint16 scancode)
{
	if (m_state != nullptr)
	{
		// try to call Lua callback
	}
	printf("keycode:%d\tmod:%d\tscancode:%d released.\n", sym, mod, scancode);
}

void CApp::OnLoop() {}

void CApp::OnRender()
{
	CSurface::OnDraw(m_screenSurface, m_defaultSurface, 0, 0, 0, 0, m_screen_width, m_screen_height);

	SDL_UpdateWindowSurface(m_window);
}

void CApp::OnCleanup()
{
	m_debugOut->outputDebugString(1, " -- Begin cleanup...\n");
	SDL_FreeSurface(m_defaultSurface);
	SDL_FreeSurface(m_screenSurface);
	SDL_Quit();
}

void CApp::OnExit() 
{
	m_debugOut->outputDebugString(1, " -- Exiting...\n");
	m_running = false;
}

/// <summary>
/// Execute a Lua script file.
/// </summary>
/// <param name="L">lua_State* Lua state that will execute the script.</param>
/// <param name="filename">string containing the name of the script file to execute.</param>
bool CApp::runScript(std::string filename)
{
	m_debugOut->outputDebugString(3, " -- Running ", filename.c_str(), "\n");

	bool result = false;

	result = luaL_dofile(m_state, filename.c_str());

	m_debugOut->outputDebugString(4, " -- ", filename.c_str(), " exited ", (result == true ? "true\n" : "false\n"));
	return result;
}

/// <summary>
/// Execute a Lua script, passing in parameters to the script.
/// </summary>
/// <param name="L">lua_State* Lua state that will execute the script.</param>
/// <param name="argCount">int containing the number of arguments.</param>
/// <param name="args">const char** containing the arguments.</param>
bool CApp::runScript(int argCount, const char** args)
{
	lua_pushinteger(m_state, argCount);  /* 1st argument */
	lua_pushlightuserdata(m_state, args); /* 2nd argument */
	int status = lua_pcall(m_state, 2, 1, 0);
	int result = lua_toboolean(m_state, -1);  /* get result */

	return (result == 0 ? false : true);
}

bool CApp::loadScripts()
{
	std::vector<std::string*>* data = new std::vector<std::string*>();
	std::string* dir = new std::string(".");
	getFileList(dir, data);
	std::string fileName = "";

	m_debugOut->outputDebugString(1, " -- Begin loading scripts...\n");

	if (data != NULL && data->size() > 0)
	{
		for (std::vector<std::string*>::iterator i = data->begin(); i != data->end(); i++)
		{
			fileName = dir->c_str();
			fileName.append("/");
			fileName.append(**i);

			m_debugOut->outputDebugString(3, " -- Loading ", fileName.c_str(), "\n");

			runScript(fileName.c_str());
		}
		m_debugOut->outputDebugString(1, " -- Scripts loaded\n");
		return true;
	}

	m_debugOut->outputDebugString(3, " -- No scripts found in ", dir->c_str(), "\n");
	return false;
}

/// <summary>
/// Takes a fully qualified path as input and returns the file name if it is a Lua script file.
/// </summary>
/// <param name="str">char string containing the file path.</param>
/// <param name="dest">reference to a string that will hold the result.</param>
/// <param name="delim">const char string pointer containing the token delimiter.</param>
void CApp::getScriptFileName(char* str, std::string& dest, const char* delim)
{
	char* nextTok;
	char* token = strtok_s(str, delim, &nextTok);
	std::string whitespaces(" \t\f\v\n\r");
	std::string tok;
	std::string result;

	while (token != NULL)
	{
		tok = token;
		if (tok.find(".lua") != std::string::npos)
		{
			result = token;
			size_t found = result.find_last_not_of(whitespaces);
			if (found != std::string::npos)
				result.erase(found + 1);
			else
				result.clear();			break;
		}
		token = strtok_s(NULL, delim, &nextTok);
	}
	dest = result.c_str();
}

/// <summary>
/// Uses the DOS dir command to get a list of files in a specified folder
/// </summary>
/// <param name="dirName">string* string containing the file path.</param>
/// <param name="target">vector(string*)* pointer to a vector of strings that will hold the result.</param>
bool CApp::getFileList(std::string *dirName, std::vector<std::string*>* target)
{
	char psBuffer[128];
	std::string command = "dir ";
	command.append(dirName->c_str());
	FILE* data = _popen(command.c_str(), "rt");
	if (data != NULL)
	{
		int line = 0;
		while (fgets(psBuffer, 128, data))
		{
			line++;
			if (line > 7)
			{
				std::string* templine = new std::string(psBuffer);
				if (templine->find(".lua") != std::string::npos)
				{
					std::string fileName;
					getScriptFileName(psBuffer, fileName, " ");
					if (fileName != "")
						target->push_back(new std::string(fileName));
				}
			}
		}
		return true;
	}
	return false;
}

// Lua interface implementation
int CApp::setAppName(lua_State* L)
{
	return 1;
}

int CApp::setResolution(lua_State* L)
{
	return 1;
}

int CApp::getResolution(lua_State* L)
{
	return 1;
}

int CApp::setBackground(lua_State* L)
{
	int top = lua_gettop(L); // should be starting path
	if (lua_isstring(L, top))
		m_backgroundName = lua_tostring(L, top);
	else
		return 0;
	
	m_defaultSurface = CSurface::OnLoad((char*)m_backgroundName.c_str(), (const SDL_Surface &)*m_screenSurface);

	if (!m_defaultSurface) {
		fprintf(stderr, "Default background could not be loaded: %s\n", SDL_GetError());
		SDL_Quit();
		return 0;
	}

	m_defaultSurface = CSurface::ScaleSurface(m_defaultSurface, m_screen_width, m_screen_height);

	return 1;
}

int CApp::getBackground(lua_State* L)
{
	lua_pushstring(L, m_backgroundName.c_str());
	return 1;
}

const char *CApp::className = "CApp";
const Luna < CApp >::FunctionType CApp::methods[] = {
	{ "setAppName", &CApp::setAppName },
	{ "setResolution", &CApp::setResolution },
	{ "getResolution", &CApp::getResolution },
	{ "setBackground", &CApp::setBackground },
	{ "getBackground", &CApp::getBackground },
	{ 0 }
};

const Luna < CApp >::PropertyType CApp::properties[] = {
	{ 0 }
};
