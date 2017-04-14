#include "CImageResource.h"

CImageResource::CImageResource(lua_State* L)
{

}

CImageResource::CImageResource()
{

}

CImageResource::~CImageResource()
{

}

EResourceType CImageResource::getType()
{
	return m_type;
}

bool CImageResource::Load(std::string filename)
{
	m_filename = std::string(filename);
	ID = "";
	return false;
}

bool CImageResource::Load(std::string filename, std::string id)
{
	m_filename = std::string(filename);
	ID = std::string(id);
	return false;
}

const char *CImageResource::className = "CImageResource";
const Luna < CImageResource >::FunctionType CImageResource::methods[] = {
	//{ "getInput", &CImageResource::getInput },
	{ 0 }
};

const Luna < CImageResource >::PropertyType CImageResource::properties[] = {
	{ 0 }
};
