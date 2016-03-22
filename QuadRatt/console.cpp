// console.cpp

#include "console.h"

CConsole::~CConsole()
{
	
}

bool CConsole::Create()
{
	if(AllocConsole())
	{
		SetConsoleOutputCP(1251);

		int hCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);

		/*
		*stdout = *(_fdopen(hCrt, "w"));
		setvbuf(stdout, NULL, _IONBF, 0);
		*stderr = *(_fdopen(hCrt, "w"));
		setvbuf(stderr, NULL, _IONBF, 0);
		*/

		freopen("CONOUT$", "w", stdout);

		return true;
	}
	return false;
}

void CConsole::Destroy()
{
	FreeConsole();
}