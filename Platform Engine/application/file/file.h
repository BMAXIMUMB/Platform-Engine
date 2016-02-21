// file.h

#ifndef _FILE_H_
#define _FILE_H_

#include <fstream>
#include <map>
#include "../../platform_engine.h"

namespace PlatformEngine
{
	class CFile
	{
	private:
		const char *path;
		bool isFile;

	public:
		PLATFORMENGINE_API	CFile();
		PLATFORMENGINE_API	~CFile();

		PLATFORMENGINE_API	bool Open(const char *path);

		PLATFORMENGINE_API	int GetInt(char *section, char *key);
		PLATFORMENGINE_API	float GetFloat(char *section, char *key);
		PLATFORMENGINE_API	LPSTR GetString(char *section, char *key);

		PLATFORMENGINE_API	void Set(char *section, char *key, char *text);
		PLATFORMENGINE_API	void Set(char *section, char *key, float value);
		PLATFORMENGINE_API	void Set(char *section, char *key, int value);
	};
};

#endif //_FILE_H_