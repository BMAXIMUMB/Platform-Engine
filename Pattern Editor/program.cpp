// program.cpp

#include "program.h"

CProgram::CProgram()
{
	programInterface = new CGInterface(app);
}

void CProgram::Start(PE::CApplication *App)
{
	this->app = App;

	programInterface->Create();
}