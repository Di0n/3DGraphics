#pragma once
#include <string>
#include <Windows.h>
namespace Util
{
	std::string getExePath()
	{
		HMODULE handle = GetModuleHandle(NULL);

		if (handle == NULL)
			return "";
		char path[MAX_PATH];
		GetModuleFileName(handle, path, (sizeof(path)));
		std::string pathStr = std::string(path);
		const size_t index = pathStr.find_last_of("/\\");

		return pathStr.substr(0, index);
	}
}