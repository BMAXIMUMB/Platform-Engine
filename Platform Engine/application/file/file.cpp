// file.cpp

#include "file.h"

extern void logprintf(std::string str);

namespace PlatformEngine
{
	CFile::CFile()
	{
		isFile = false;
		path = "";
	}

	CFile::~CFile()
	{

	}

	bool CFile::Create(const char *path)
	{
		if(!Open(path))
		{
			fopen(path, "a");
			return true;
		}

		return false;
	}

	bool CFile::Open(const char * path)
	{
		if(fopen(path, "r") != 0)
		{
			this->path = path;
			isFile = true;
			return true;
		}

		return false;
	}

	int CFile::GetInt(char *section, char *key)
	{
		return GetPrivateProfileInt(section, key, NULL, path);
	}
	
	float CFile::GetFloat(char *section, char *key)
	{
		char *buff = new char[30];
		float val;
		GetPrivateProfileStringA(section, key, NULL, buff, 256, path);
		val = atof(buff);
		delete buff;
		return val;
	}

	LPSTR CFile::GetString(char *section, char *key)
	{
		char *buff = new char[256];
		GetPrivateProfileStringA(section, key, NULL, buff, 256, path);

		return buff;
	}

	////////////////////////////////////////////////////////////////////////////////

	void CFile::Set(char *section, char *key, char *text)
	{
		WritePrivateProfileString(section, key, text, path);
	}

	void CFile::Set(char *section, char *key, int value)
	{
		char buff[30];
		itoa(value, buff, 10);
		WritePrivateProfileString(section, key, buff, path);
	}

	void CFile::Set(char *section, char *key, float value)
	{
		char buff[30];
		sprintf(buff, "%f", value);
		WritePrivateProfileString(section, key, buff, path);
	}
};