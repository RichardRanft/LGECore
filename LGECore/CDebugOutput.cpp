#include "CDebugOutput.h"
#include "Windows.h"

CDebugOutput::CDebugOutput()
{
}

CDebugOutput::~CDebugOutput()
{
}

void CDebugOutput::outputDebugString(int count, ...)
{
	std::string message;

	va_list msg;

	va_start(msg, count);
	for (int i = 0; i < count; i++)
	{
		message.append(va_arg(msg, char*));
	}
	va_end(msg);

	// now for the fun part - convert std::string to LPCWSTR
	wchar_t szBuff[4096];
	mbstowcs(szBuff, message.c_str(), 4096);
	OutputDebugString(szBuff);
}