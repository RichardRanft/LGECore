#include "CResourceInstance.h"

CResourceInstance::CResourceInstance()
{
	m_state = luaL_newstate();
}

CResourceInstance::CResourceInstance(lua_State* l)
{
	m_state = l;
}

CResourceInstance::~CResourceInstance()
{
}

std::string CResourceInstance::getFileName()
{
	return std::string(m_filename.c_str());
}

EResourceType CResourceInstance::getType()
{
	return m_type;
}

bool CResourceInstance::Load(std::string filename)
{
	m_filename = std::string(filename);
	return false;
}

bool CResourceInstance::Load(std::string filename, std::string id)
{
	m_filename = std::string(filename);
	ID = std::string(id);
	return false;
}

// Lua interface
int CResourceInstance::getName(lua_State* L)
{
	return 1;
}

int CResourceInstance::getRefCount(lua_State* L)
{
	return 1;
}

const char *CResourceInstance::className = "CResourceInstance";
const Luna < CResourceInstance >::FunctionType CResourceInstance::methods[] = {
	{ "getName", &CResourceInstance::getName },
	{ "getRefCount", &CResourceInstance::getRefCount },
	{ 0 }
};

const Luna < CResourceInstance >::PropertyType CResourceInstance::properties[] = {
	{ 0 }
};
