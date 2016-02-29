// program.h

#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include "main.h"
#include "game\game.h"
#include "console.h"

class CProgram
{
private:
	HINSTANCE hInstance;
	HINSTANCE hPrevInstance;

	CGame *game;
	CConsole *console;
	PE::CApplication *app;

public:
	CProgram(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	~CProgram();

	int Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

	void InitGL(void);
	bool Start(void);

	bool LoadShaders(void);

	CGame* GetGame(void) { return game; }

	// CALLBACKS
	void onKeyDown(int);
	void onKeyUp(int);
	void onMouseDown(int, int, int);
	void onMouseUp(int, int, int);
	void onMouseMove(int, int);

	void LoopFunction(void);
};

#endif /*_PROGRAM_H_*/