#include "CResourceInstance.h"

CResourceInstance::CResourceInstance()
{

}

CResourceInstance::~CResourceInstance()
{

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