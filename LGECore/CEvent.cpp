#include "CEvent.h"

CEvent::CEvent() 
{
	m_state = luaL_newstate();
}

CEvent::CEvent(lua_State* L)
{
	m_state = L;
}

CEvent::~CEvent()
{
	m_state = nullptr;
}

void CEvent::OnEvent(SDL_Event* Event)
{
	switch (Event->type)
	{
		case SDL_WINDOWEVENT:
		{
			switch (Event->window.event)
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
					OnWindowResized(Event->window.data1, Event->window.data2);
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
			OnKeyDown(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.scancode);
			break;
		}
		case SDL_KEYUP:
		{
			OnKeyUp(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.scancode);
			break;
		}
		case SDL_MOUSEMOTION:
		{
			OnMouseMove(Event->motion.x, Event->motion.y, Event->motion.xrel, Event->motion.yrel, (Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT)) != 0, (Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0, (Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			switch (Event->button.button)
			{
				case SDL_BUTTON_LEFT:
				{
					OnLButtonDown(Event->button.x, Event->button.y);
					break;
				}
				case SDL_BUTTON_RIGHT:
				{
					OnRButtonDown(Event->button.x, Event->button.y);
					break;
				}
				case SDL_BUTTON_MIDDLE:
				{
					OnMButtonDown(Event->button.x, Event->button.y);
					break;
				}
			}
			break;
		}

		case SDL_MOUSEBUTTONUP:
		{
			switch (Event->button.button)
			{
				case SDL_BUTTON_LEFT:
				{
					OnLButtonUp(Event->button.x, Event->button.y);
					break;
				}
				case SDL_BUTTON_RIGHT:
				{
					OnRButtonUp(Event->button.x, Event->button.y);
					break;
				}
				case SDL_BUTTON_MIDDLE:
				{
					OnMButtonUp(Event->button.x, Event->button.y);
					break;
				}
			}
			break;
		}

		//Star getting things from here man!
		case SDL_JOYAXISMOTION:
		{
			OnJoyAxis(Event->jaxis.which, Event->jaxis.axis, Event->jaxis.value);
			break;
		}
		case SDL_JOYBALLMOTION:
		{
			OnJoyBall(Event->jball.which, Event->jball.ball, Event->jball.xrel, Event->jball.yrel);
			break;
		}
		case SDL_JOYHATMOTION:
		{
			OnJoyHat(Event->jhat.which, Event->jhat.hat, Event->jhat.value);
			break;
		}
		case SDL_JOYBUTTONDOWN:
		{
			OnJoyButtonDown(Event->jbutton.which, Event->jbutton.button);
			break;
		}
		case SDL_JOYBUTTONUP:
		{
			OnJoyButtonUp(Event->jbutton.which, Event->jbutton.button);
			break;
		}
		default:
		{
			OnUser(Event->user.type, Event->user.code, Event->user.data1, Event->user.data2);
			break;
		}
	}
}

void CEvent::OnExit() {}

void CEvent::OnKeyDown(SDL_Keycode sym, Uint16 mod, Uint16 scancode)
{
	if (m_state != nullptr)
	{
		// try to call Lua callback
	}
	printf("keycode:%d\tmod:%d\tscancode:%d pressed.\n", sym, mod, scancode);
}

void CEvent::OnKeyUp(SDL_Keycode sym, Uint16 mod, Uint16 scancode)
{
	if (m_state != nullptr)
	{
		// try to call Lua callback
	}
	printf("keycode:%d\tmod:%d\tscancode:%d released.\n", sym, mod, scancode);
}

void CEvent::OnMouseMove(int mx, int my, int relx, int rely, bool Left, bool Right, bool Middle)
{
	if (m_state != nullptr)
	{
		// try to call Lua callback
	}
	printf("x:%d\ty:%d\n", mx, my);
}

void CEvent::OnLButtonDown(int mx, int my)
{
	if (m_state != nullptr)
	{
		// try to call Lua callback
	}
	printf("Left Click pressed in x:%d\ty:%d\n", mx, my);
}

void CEvent::OnLButtonUp(int mx, int my)
{
	if (m_state != nullptr)
	{
		// try to call Lua callback
	}
	printf("Left Click unpressed in x:%d\ty:%d\n", mx, my);
}

void CEvent::OnRButtonDown(int mx, int my)
{
	if (m_state != nullptr)
	{
		// try to call Lua callback
	}
	printf("Right Click pressed in x:%d\ty:%d\n", mx, my);
}

void CEvent::OnRButtonUp(int mx, int my)
{
	if (m_state != nullptr)
	{
		// try to call Lua callback
	}
	printf("Right Click unpressed in x:%d\ty:%d\n", mx, my);
}

void CEvent::OnMButtonDown(int mx, int my)
{
	if (m_state != nullptr)
	{
		// try to call Lua callback
	}
	printf("Middle Click pressed in x:%d\ty:%d\n", mx, my);
}

void CEvent::OnMButtonUp(int mx, int my)
{
	if (m_state != nullptr)
	{
		// try to call Lua callback
	}
	printf("Middle Click unpressed in x:%d\ty:%d\n", mx, my);
}

void CEvent::OnMouseFocus()
{
	if (m_state != nullptr)
	{
		// try to call Lua callback
	}
	printf("Mouse entered the window.\n");
}

void CEvent::OnMouseBlur()
{
	if (m_state != nullptr)
	{
		// try to call Lua callback
	}
	printf("Mouse left the window.\n");
}

void CEvent::OnInputFocus()
{
	if (m_state != nullptr)
	{
		// try to call Lua callback
	}
	printf("Keyboard focus set to the window.\n");
}

void CEvent::OnInputBlur()
{
	if (m_state != nullptr)
	{
		// try to call Lua callback
	}
	printf("Keyboar losed focus on the window.\n");
}

void CEvent::OnWindowResized(int data1, int data2)
{
	if (m_state != nullptr)
	{
		// try to call Lua callback
	}
	printf("Window Resized to: width:%d\theight:%d\n", data1, data2);
}

void CEvent::OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value)
{
	if (m_state != nullptr)
	{
		// try to call Lua callback
	}
}

void CEvent::OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel) 
{
	if (m_state != nullptr)
	{
		// try to call Lua callback
	}
}

void CEvent::OnJoyHat(Uint8 which, Uint8 hat, Uint8 button) 
{
	if (m_state != nullptr)
	{
		// try to call Lua callback
	}
}

void CEvent::OnJoyButtonDown(Uint8 which, Uint8 button) 
{
	if (m_state != nullptr)
	{
		// try to call Lua callback
	}
}

void CEvent::OnJoyButtonUp(Uint8 which, Uint8 button) 
{
	if (m_state != nullptr)
	{
		// try to call Lua callback
	}
}

void CEvent::OnUser(Uint8 type, int code, void* data1, void* data2) 
{
	if (m_state != nullptr)
	{
		// try to call Lua callback
	}
}

int CEvent::error(const char* msg, ...)
{
	if (m_state == nullptr)
	{
		printf("CEvent member m_state is null.");
		return 2;
	}
	if (lua_isnil(m_state, -1))
	{
		printf("Error object is not a string");
	}
	int status = lua_error(m_state);
	if (msg == nullptr)
	{
		msg = lua_tostring(m_state, -1);
	}
	lua_getfield(m_state, LUA_REGISTRYINDEX, "debug");
	if (!lua_istable(m_state, -1))
	{
		lua_pop(m_state, 1);
		return 1;
	}
	lua_getfield(m_state, -1, "traceback");
	if(!lua_isfunction(m_state, -1))
	{
		lua_pop(m_state, 2);
		return 1;
	}
	lua_pushvalue(m_state, 1);
	lua_pushinteger(m_state, 2);
	lua_call(m_state, 2, 1);

	printf("[LUA] Error: %s\n", lua_tostring(m_state, -1));
	va_list arglist;
	va_start(arglist, msg);
	vprintf(msg, arglist);
	lua_pop(m_state, 1);

	return 0;
}

void CEvent::CallLuaFunction(const char* funcName, const char* funcSig, ...)
{
	va_list vl;
	int narg, nres;  /* number of arguments and results */

	va_start(vl, funcSig);
	lua_getglobal(m_state, funcName);  /* get function */

							 /* push arguments */
	narg = 0;
	while (*funcSig) {  /* push arguments */
		switch (*funcSig++) {

		case 'd':  /* double argument */
			lua_pushnumber(m_state, va_arg(vl, double));
			break;

		case 'i':  /* int argument */
			lua_pushnumber(m_state, va_arg(vl, int));
			break;

		case 's':  /* string argument */
			lua_pushstring(m_state, va_arg(vl, char *));
			break;

		case '>':
			goto endwhile;

		default:
			error("invalid option (%c)", *(funcSig - 1));
		}
		narg++;
		luaL_checkstack(m_state, 1, "too many arguments");
	} endwhile:

	/* do the call */
	nres = strlen(funcSig);  /* number of expected results */
	if (lua_pcall(m_state, narg, nres, 0) != 0)  /* do the call */
		error("error running function `%s': %s",
			funcName, lua_tostring(m_state, -1));

	/* retrieve results */
	nres = -nres;  /* stack index of first result */
	while (*funcSig) {  /* get results */
		switch (*funcSig++) {

		case 'd':  /* double result */
			if (!lua_isnumber(m_state, nres))
				error("wrong result type");
			*va_arg(vl, double *) = lua_tonumber(m_state, nres);
			break;

		case 'i':  /* int result */
			if (!lua_isnumber(m_state, nres))
				error("wrong result type");
			*va_arg(vl, int *) = (int)lua_tonumber(m_state, nres);
			break;

		case 's':  /* string result */
			if (!lua_isstring(m_state, nres))
				error("wrong result type");
			*va_arg(vl, const char **) = lua_tostring(m_state, nres);
			break;

		default:
			error("invalid option (%c)", *(funcSig - 1));
		}
		nres++;
	}
	va_end(vl);
}

// Lua interface
const char *CEvent::className = "CEvent";
const Luna < CEvent >::FunctionType CEvent::methods[] = {
	//{ "loadImage", &CEvent::loadImage },
	//{ "LoadSound", &CEvent::loadSound },
	{ 0 }
};

const Luna < CEvent >::PropertyType CEvent::properties[] = {
	{ 0 }
};
