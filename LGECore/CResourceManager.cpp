#include "CResourceManager.h"

CResourceManager::CResourceManager()
{

}

CResourceManager::CResourceManager(lua_State* L)
{

}

CResourceManager::~CResourceManager()
{

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

const char *CResourceManager::className = "CResourceManager";
const Luna < CResourceManager >::FunctionType CResourceManager::methods[] = {
	//{ "getInput", &CResourceManager::getInput },
	{ 0 }
};

const Luna < CResourceManager >::PropertyType CResourceManager::properties[] = {
	{ 0 }
};
