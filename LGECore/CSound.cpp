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

const char *CSound::className = "CSound";
const Luna < CSound >::FunctionType CSound::methods[] = {
	//{ "getInput", &CSound::getInput },
	{ 0 }
};

const Luna < CSound >::PropertyType CSound::properties[] = {
	{ 0 }
};
