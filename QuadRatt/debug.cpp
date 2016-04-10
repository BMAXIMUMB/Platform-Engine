// debug.cpp

#include "debug.h"

CDebug::CDebug(PE::CApplication *App)
{
	this->app = App;
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
	ts.text = L"PCount:";
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
		char str[50];
		sprintf(str, "PCount: %d", app->world->GetParticleCount());
		textPc->SetText(str);

		sprintf(str, "FPS: %d", app->fpsMeter->GetFPS());
		textFps->SetText(str);
	}
}