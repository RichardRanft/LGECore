#include "CGuiBase.h"

CGuiBase::CGuiBase()
{
	m_state = luaL_newstate();
}

CGuiBase::CGuiBase(lua_State* l)
{
	m_state = l;
}

CGuiBase::~CGuiBase()
{
	m_state = nullptr;
}

void CGuiBase::OnEvent(SDL_Event* event)
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


// Lua interface
int CGuiBase::setName(lua_State* L)
{
	return 1;
}

int CGuiBase::getName(lua_State* L)
{
	return 1;
}

const char *CGuiBase::className = "CGuiBase";
const Luna < CGuiBase >::FunctionType CGuiBase::methods[] = {
	{ "setName", &CGuiBase::setName },
	{ "getName", &CGuiBase::getName },
	{ 0 }
};

const Luna < CGuiBase >::PropertyType CGuiBase::properties[] = {
	{ 0 }
};
