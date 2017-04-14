#include "CResourceManager.h"

CResourceManager::CResourceManager()
{
	m_state = luaL_newstate();
}

CResourceManager::CResourceManager(lua_State* L)
{
	m_state = L;
}

CResourceManager::~CResourceManager()
{
	m_state = nullptr;
}

bool CResourceManager::Load(std::string path, EResourceType rtype)
{
	switch (rtype)
	{
		case SOUND:
			{
				CSoundResource *res = new CSoundResource(m_state);
				m_reslist.push_back(res);
			}
			break;
		case IMAGE:
			{
				CImageResource *res = new CImageResource(m_state);
				m_reslist.push_back(res);
			}
			break;
		default:
			break;
	}
	return false;
}

void CResourceManager::Clear()
{
	m_reslist.clear();
}

// Lua interface
int CResourceManager::getResourceList(lua_State* L)
{
	int count = 0;
	for (std::vector<CResourceInstance*>::iterator it = m_reslist.begin(); it != m_reslist.end(); it++)
	{
		std::string temp = (*it)->getFileName();
		temp.append(":");
		EResourceType type = (*it)->getType();
		switch (type)
		{
		case SOUND:
			temp.append("SOUND");
			break;
		case IMAGE:
			temp.append("IMAGE");
			break;
		default:
			break;
		}
		lua_pushstring(L, temp.c_str());
	}
	return count;
}

int CResourceManager::loadImage(lua_State* L)
{
	return 1;
}

int CResourceManager::loadSound(lua_State* L)
{
	return 1;
}

const char *CResourceManager::className = "CResourceManager";
const Luna < CResourceManager >::FunctionType CResourceManager::methods[] = {
	{ "loadImage", &CResourceManager::loadImage },
	{ "LoadSound", &CResourceManager::loadSound },
	{ 0 }
};

const Luna < CResourceManager >::PropertyType CResourceManager::properties[] = {
	{ 0 }
};
