#pragma once

#include "luna.h"
#include "CResourceInstance.h"
#include "CSound.h"

class CSoundResource : public CResourceInstance
{
private:
	std::string m_filename;

public:
	CSoundResource();
	CSoundResource(lua_State *L);
	~CSoundResource();

	bool Load(std::string filename);
	bool Load(std::string filename, std::string id);

	static const char *className;
	static const Luna <CSoundResource>::FunctionType methods[];
	static const Luna <CSoundResource>::PropertyType properties[];

	bool isExisting; // This is used by Luna to see whether it's been created by createFromExisting.  Don't set it.
	bool isPrecious; // This is used to tell Luna not to garbage collect the object, in case other objects might reference it.  Set it in your class's constructor.

	// Lua interface
	//int getInput(lua_State* L);
};