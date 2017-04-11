#pragma once
#include <string>
#include <vector>

class CResourceInstance
{
private:
	std::string m_filename;

public:
	CResourceInstance();
	~CResourceInstance();

	std::string ID;

	virtual bool Load(std::string filename);
	virtual bool Load(std::string filename, std::string id);
};