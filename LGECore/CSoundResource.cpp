#include "CSoundResource.h"

CSoundResource::CSoundResource()
{

}

CSoundResource::CSoundResource(lua_State *L)
{

}

CSoundResource::~CSoundResource()
{

}

bool CSoundResource::Load(std::string filename)
{
	m_filename = std::string(filename);
	ID = "";
	return false;
}

bool CSoundResource::Load(std::string filename, std::string id)
{
	m_filename = std::string(filename);
	ID = std::string(id);
	return false;
}

const char *CSoundResource::className = "CSoundResource";
const Luna < CSoundResource >::FunctionType CSoundResource::methods[] = {
	//{ "getInput", &CSoundResource::getInput },
	{ 0 }
};

const Luna < CSoundResource >::PropertyType CSoundResource::properties[] = {
	{ 0 }
};
