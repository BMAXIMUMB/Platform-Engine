// debug.cpp

#include "debug.h"
#include "game\game.h"

CDebug::CDebug(PE::CApplication *App, CGame *game)
{
	this->app = App;
	this->game = game;

	debugShowed = false;
}

CDebug::~CDebug()
{

}

void CDebug::ShowDebugInfo()
{
	TextSettings ts;

	ts.font = app->fontManager->Load("resources\\fonts\\arial.ttf", "Arial");
	ts.posX = 0.0;
	ts.posY = 690.0;
	ts.color = {1, 1, 1, 1};
	ts.text = L"FPS:";
	ts.name = "t1";
	ts.fontsize = 15;

	textFps = app->GUI->CreateText(ts);
	textFps->Show();


	ts.font = app->fontManager->Load("resources\\fonts\\arial.ttf", "Arial");
	ts.posX = 0.0;
	ts.posY = 670.0;
	ts.color = {1, 1, 1, 1};
	ts.text = L"posX:";
	ts.name = "t2";
	ts.fontsize = 15;

	textPc = app->GUI->CreateText(ts);
	textPc->Show();


	debugShowed = true;
}

void CDebug::HideDebugInfo()
{
	textFps->Hide();
	textPc->Hide();

	debugShowed = false;
}

void CDebug::Update()
{
	if(debugShowed)
	{
		char str[80];
		float x, y;
		float cpos[2] = { 0.f, 0.f };
		static float maxY = 0;

		game->GetLevel()->GetPlayer()->GetPosition(x, y);
		if(y > maxY) maxY = y;
		if(game->GetWorld()->camera != nullptr)
		{
			game->GetWorld()->camera->GetPosition(cpos[0], cpos[1]);
		}
		
		sprintf(str, "posX: %.1f, posY: %.1f (max %.1f)", x, y, maxY);
		textPc->SetText(str);

		sprintf(str, "FPS: %d | Obj: %d", app->fpsMeter->GetFPS(),
			game->GetLevel()->GetMap()->GetObjectCount());
		textFps->SetText(str);
	}
}