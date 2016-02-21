// program.h
#pragma once

#include "main.h"

class CProgram
{
private:
	PE::CApplication *app;
	Gui::CBox *mainBox;

public:
	void Start(PE::CApplication *App);
	void InterfaceCreate(void);
};