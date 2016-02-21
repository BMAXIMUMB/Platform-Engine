// input.cpp

#include "input.h"

extern CProgram *gProgram;

void KeyDown(int key)
{
	gProgram->onKeyDown(key);
}

void KeyUp(int key)
{
	gProgram->onKeyUp(key);
}

void MouseDown(int button, int x, int y)
{
	gProgram->onMouseDown(button, x, y);
}

void MouseUp(int button, int x, int y)
{
	gProgram->onMouseUp(button, x, y);
}

void MouseMove(int x, int y)
{
	gProgram->onMouseMove(x, y);
}