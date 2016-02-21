// console.cpp

#include "console.h"

bool CConsole::Create()
{
	if(AllocConsole())
	{
		int hCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);

		*stdout = *(_fdopen(hCrt, "w"));
		setvbuf(stdout, NULL, _IONBF, 0);
		*stderr = *(_fdopen(hCrt, "w"));
		setvbuf(stderr, NULL, _IONBF, 0);

		return true;
	}
	return false;
}

void CConsole::Destroy()
{
	FreeConsole();
}