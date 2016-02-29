// program.h
#pragma once

#include "main.h"
#include "ginterface.h"

class CProgram
{
private:
	PE::CApplication *app;

	CGInterface *programInterface;

public:
	CProgram();
	~CProgram();

	void Start(PE::CApplication *App);

	CGInterface* GetGui(void) { return programInterface; }
};