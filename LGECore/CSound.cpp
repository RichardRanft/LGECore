#include "CSound.h"

CSound::CSound()
{

}

CSound::CSound(lua_State* L)
{

}

CSound::~CSound()
{

}

// Lua interface
int CSound::getName(lua_State* L)
{
	return 1;
}

int CSound::play(lua_State* L)
{
	return 1;
}

int CSound::stop(lua_State* L)
{
	return 1;
}

int CSound::setChannel(lua_State* L)
{
	return 1;
}

int CSound::getChannel(lua_State* L)
{
	return 1;
}

int CSound::setVolume(lua_State* L)
{
	return 1;
}

int CSound::getVolume(lua_State* L)
{
	return 1;
}

const char *CSound::className = "CSound";
const Luna < CSound >::FunctionType CSound::methods[] = {
	{ "getName", &CSound::getName },
	{ "play", &CSound::play },
	{ "stop", &CSound::stop },
	{ "setChannel", &CSound::setChannel },
	{ "getChannel", &CSound::getChannel },
	{ "setVolume", &CSound::setVolume },
	{ "getVolume", &CSound::getVolume },
	{ 0 }
};

const Luna < CSound >::PropertyType CSound::properties[] = {
	{ 0 }
};
