#include "stdafx.h"
#include <string>
#include "RegisterLunaClasses.h"

/// <summary>
/// Takes a fully qualified path as input and returns the file name if it is a Lua script file.
/// </summary>
/// <param name="str">char string containing the file path.</param>
/// <param name="dest">reference to a string that will hold the result.</param>
/// <param name="delim">const char string pointer containing the token delimiter.</param>
void getScriptFileName(char* str, std::string& dest, const char* delim)
{
	char* nextTok;
	char* token = strtok_s(str, delim, &nextTok);
	std::string whitespaces(" \t\f\v\n\r");
	std::string tok;
	std::string result;

	while (token != NULL)
	{
		tok = token;
		if (tok.find(".lua") != std::string::npos)
		{
			result = token;
			size_t found = result.find_last_not_of(whitespaces);
			if (found != std::string::npos)
				result.erase(found + 1);
			else
				result.clear();			break;
		}
		token = strtok_s(NULL, delim, &nextTok);
	}
	dest = result.c_str();
}

/// <summary>
/// Uses the DOS dir command to get a list of files in a specified folder
/// </summary>
/// <param name="dirName">string* string containing the file path.</param>
/// <param name="target">vector(string*)* pointer to a vector of strings that will hold the result.</param>
bool getFileList(std::string *dirName, std::vector<std::string*>* target)
{
	char psBuffer[128];
	std::string command = "dir ";
	command.append(dirName->c_str());
	FILE* data = _popen(command.c_str(), "rt");
	if (data != NULL)
	{
		int line = 0;
		while (fgets(psBuffer, 128, data))
		{
			line++;
			if (line > 7)
			{
				std::string* templine = new std::string(psBuffer);
				if (templine->find(".lua") != std::string::npos)
				{
					std::string fileName;
					getScriptFileName(psBuffer, fileName, " ");
					if (fileName != "")
						target->push_back(new std::string(fileName));
				}
			}
		}
		return true;
	}
	return false;
}

/// <summary>
/// Execute a Lua script file.
/// </summary>
/// <param name="L">lua_State* Lua state that will execute the script.</param>
/// <param name="filename">string containing the name of the script file to execute.</param>
bool runScript(lua_State* state, std::string filename)
{
	//m_debugOut->outputDebugString(3, " -- Running ", filename.c_str(), "\n");

	bool result = false;

	result = luaL_dofile(state, filename.c_str());

	//m_debugOut->outputDebugString(4, " -- ", filename.c_str(), " exited ", (result == true ? "true\n" : "false\n"));
	return result;
}

/// <summary>
/// Execute a Lua script, passing in parameters to the script.
/// </summary>
/// <param name="L">lua_State* Lua state that will execute the script.</param>
/// <param name="argCount">int containing the number of arguments.</param>
/// <param name="args">const char** containing the arguments.</param>
bool runScript(lua_State* state, std::string filename, int argCount, const char** args)
{
	luaL_loadfile(state, filename.c_str());
	lua_pushinteger(state, argCount);  /* 1st argument */
	lua_pushlightuserdata(state, args); /* 2nd argument */
	int status = lua_pcall(state, 2, 1, 0);
	int result = lua_toboolean(state, -1);  /* get result */

	return (result == 0 ? false : true);
}

bool loadScript(lua_State* state, std::string filename)
{
	//m_debugOut->outputDebugString(3, " -- Running ", filename.c_str(), "\n");

	bool result = false;

	result = luaL_loadfile(state, filename.c_str());

	//m_debugOut->outputDebugString(4, " -- ", filename.c_str(), " exited ", (result == true ? "true\n" : "false\n"));
	return result;
}

bool loadScripts(lua_State* state)
{
	std::vector<std::string*>* data = new std::vector<std::string*>();
	std::string* dir = new std::string(".");
	getFileList(dir, data);
	std::string fileName = "";

	//m_debugOut->outputDebugString(1, " -- Begin loading scripts...\n");

	if (data != NULL && data->size() > 0)
	{
		for (std::vector<std::string*>::iterator i = data->begin(); i != data->end(); i++)
		{
			fileName = dir->c_str();
			fileName.append("/");
			fileName.append(**i);

			//m_debugOut->outputDebugString(3, " -- Loading ", fileName.c_str(), "\n");

			loadScript(state, fileName.c_str());
		}
		//m_debugOut->outputDebugString(1, " -- Scripts loaded\n");
		return true;
	}

	//m_debugOut->outputDebugString(3, " -- No scripts found in ", dir->c_str(), "\n");
	return false;
}

int main(int argc, char* argv[]) {
	lua_State* state = luaL_newstate();
	luaL_openlibs(state);

	registerLuaClasses(state);

	//CApp theApp(state, 1024, 600);

	//int ret = theApp.OnExecute();
	loadScripts(state);
	std::string mainscript = "main.lua";
	runScript(state, mainscript, argc, (const char**)argv);

	lua_close(state);

	return 0;
}