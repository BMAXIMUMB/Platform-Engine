#include "main.h"
#include "program.h"

/*void MouseDown(int button, int x, int y)
{
	TestText->SetText(L"ÏÈÇÄÀ ÁËßÒÜ ÐÓËÞ ÅÁÀÒÜ ÔÏÑ ÏÐÎÑÅÄÀÅÒ ÑÓÊÀ");
	int ws[2];
	app->GetWindowSize(ws[0], ws[1]);
	World->CreateObjectQuad((x + World->Camera->posX - World->Camera->offset_x) - ws[0] / 2, (((y - 720)*-1) + World->Camera->posY - World->Camera->offset_y) - ws[1] / 2, 32, 32, app->SprManager->Get("block"));
}*/

CProgram *gProgram;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	gProgram = new CProgram(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	gProgram->Main(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}

void ShutDown()
{
	delete gProgram;
}

void loopF()
{
	if(gProgram != NULL)
	{
		gProgram->LoopFunction();
	}
}

void OnObjCollision(PE::CContact *c)
{
	gProgram->GetGame()->onObjectCollision(c);
}

