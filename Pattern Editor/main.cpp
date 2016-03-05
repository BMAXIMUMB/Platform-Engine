// main.cpp

#include "main.h"
#include "program.h"

PE::CApplication *App;
CProgram *gProgram;

void InitGL()
{
	glClearColor(0.3f, 0.3f, 0.3f, 0.0);					
	glClearDepth(1.0f);									
	glEnable(GL_TEXTURE_2D);							
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	App = new PE::CApplication;
	ApplicationSettings as;

	as.wfullscreen = false;
	as.wbits = 32;
	as.wheight = WINDOW_SIZE_Y;
	as.wwidth = WINDOW_SIZE_X;
	as.wtitle = "QuadRatt Pattern Editor";
	App->Init(as);

	InitGL();

	gProgram = new CProgram;
	gProgram->Start(App);

	App->Run();
}