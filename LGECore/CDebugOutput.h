#pragma once
#include <string>
#include <stdarg.h>
#include <stdlib.h>

class CDebugOutput
{
public:
	CDebugOutput();
	~CDebugOutput();

	void outputDebugString(int count, ...);
};
