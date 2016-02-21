// program.cpp

#include "program.h"

void CProgram::Start(PE::CApplication *App)
{
	this->app = App;
	InterfaceCreate();
}

void CProgram::InterfaceCreate()
{
	GuiElementSettings ges;
	ges.posX = 100;
	ges.posY = 100;
	ges.sizeX = 100;
	ges.sizeY = 100;
	ges.name = "mainBox";
	mainBox = app->GUI->CreateBox(ges);

	app->GUI->Show("mainBox");
}