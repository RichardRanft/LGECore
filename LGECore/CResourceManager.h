#pragma once
#include "luna.h"
#include "CResourceInstance.h"
#include "CImageResource.h"
#include "CSoundResource.h"
#include "EResourceTypes.h"
#include <string>
#include <vector>

class CResourceManager
{
private:
	lua_State* m_state;
	std::vector<CResourceInstance*> m_reslist;
	
public:
	CResourceManager();
	CResourceManager(lua_State* L);
	~CResourceManager();

	bool Load(std::string path, EResourceType rtype);

	static const char *className;
	static const Luna <CResourceManager>::FunctionType methods[];
	static const Luna <CResourceManager>::PropertyType properties[];

	bool isExisting; // This is used by Luna to see whether it's been created by createFromExisting.  Don't set it.
	bool isPrecious; // This is used to tell Luna not to garbage collect the object, in case other objects might reference it.  Set it in your class's constructor.

					 // Lua interface
					 //int getInput(lua_State* L);
};