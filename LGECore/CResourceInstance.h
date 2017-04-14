#pragma once
#include "luna.h"
#include "EResourceTypes.h"
#include <string>
#include <vector>

class CResourceInstance
{
private:
	lua_State* m_state;
	std::string m_filename;
	EResourceType m_type;

public:
	CResourceInstance();
	CResourceInstance(lua_State* l);
	~CResourceInstance();

	std::string ID;

	virtual std::string getFileName();
	virtual EResourceType getType();

	virtual bool Load(std::string filename);
	virtual bool Load(std::string filename, std::string id);

	static const char *className;
	static const Luna <CResourceInstance>::FunctionType methods[];
	static const Luna <CResourceInstance>::PropertyType properties[];

	bool isExisting; // This is used by Luna to see whether it's been created by createFromExisting.  Don't set it.
	bool isPrecious; // This is used to tell Luna not to garbage collect the object, in case other objects might reference it.  Set it in your class's constructor.

	// Lua interface
	int getName(lua_State* L);
	int getRefCount(lua_State* L);
};