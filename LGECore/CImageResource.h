#pragma once

#include "luna.h"
#include "CResourceInstance.h"
#include "CSurface.h"

class CImageResource : public CResourceInstance
{
private:
	std::string m_filename;

public:
	CImageResource();
	CImageResource(lua_State* L);
	~CImageResource();

	bool Load(std::string filename);
	bool Load(std::string filename, std::string id);

	static const char *className;
	static const Luna <CImageResource>::FunctionType methods[];
	static const Luna <CImageResource>::PropertyType properties[];

	bool isExisting; // This is used by Luna to see whether it's been created by createFromExisting.  Don't set it.
	bool isPrecious; // This is used to tell Luna not to garbage collect the object, in case other objects might reference it.  Set it in your class's constructor.

	// Lua interface
	//int getInput(lua_State* L);
};