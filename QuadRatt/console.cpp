// console.cpp

#include "console.h"

CConsole::CConsole()
{
	isCreated = false;
}

CConsole::~CConsole()
{
	
}

bool CConsole::Create()
{
	if(AllocConsole())
	{
		SetConsoleOutputCP(1251);

		int hCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);

		freopen("CONOUT$", "w", stdout);

		isCreated = true;
		return true;
	}
	return false;
}

void CConsole::Destroy()
{
	isCreated = false;
	FreeConsole();
}

bool CConsole::IsCreated()
{
	return isCreated;
}