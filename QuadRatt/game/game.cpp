// game.cpp

#include "game.h"
#include "gamegui.h"
#include <stdio.h>

CGame::CGame(PE::CApplication *App)
{
	this->app		= App;

	WorldSettings	ws;
	ws.collision	= true;
	ws.groundLevel	= 150.f;

	world			= new PlatformEngine::CWorld(app, ws);
	level			= new CLevel(this);
	gInterface		= new CInterface(this);
	debugInfo		= new CDebug(app, this);
	state			= new CGameState(this);


	world->physics->SetGravity(/*25120*/23900);
	world->SetCollisionFunction(OnObjCollision);

	gInterface->ShowLoadingImage();
}

CGame::~CGame()
{
	delete level;
	delete world;
	delete gInterface;
	delete debugInfo;
}

void CGame::ShowDebugInfo()
{
	debugInfo->ShowDebugInfo();
}

void CGame::Start()
{
	
}

void CGame::Restart()
{

}

void CGame::DebugInfoUpdate()
{
	debugInfo->Update();
}

// Load Resources
void CGame::LoadResources()
{
	LoadSprites();
	LoadFonts();
	gInterface->CreateGUI();
}

void CGame::LoadSprites()
{
	//game sprites
	app->spriteManager->Load("resources\\sprites\\player.sprite", "s_player");
	app->spriteManager->Load("resources\\sprites\\block.sprite", "s_block");
	app->spriteManager->Load("resources\\sprites\\gr.sprite", "s_ground");
	app->spriteManager->Load("resources\\sprites\\smoke.sprite", "s_smoke");
	app->spriteManager->Load("resources\\sprites\\background.sprite", "s_bg");
	app->spriteManager->Load("resources\\sprites\\loading.sprite", "s_loading");
	app->spriteManager->Load("resources\\sprites\\gl.sprite", "s_gl");
	app->spriteManager->Load("resources\\sprites\\column.sprite", COLUMN_SPRITE_NAME);
	app->spriteManager->Load("resources\\sprites\\mini_platform.sprite", "s_mplatform");
	app->spriteManager->Load("resources\\sprites\\triangle.sprite", "s_triangle");

	// gui sprites
	app->spriteManager->Load("resources\\sprites\\gui\\gui_icon_sound_off.sprite", "g_icon_sound_off");
	app->spriteManager->Load("resources\\sprites\\gui\\gui_icon_sound_on.sprite", "g_icon_sound_on");
	app->spriteManager->Load("resources\\sprites\\gui\\gui_icon_star.sprite", "g_icon_star");
	app->spriteManager->Load("resources\\sprites\\gui\\gui_icon_stats.sprite", "g_icon_stats");
	app->spriteManager->Load("resources\\sprites\\gui\\gui_icon_pause.sprite", "g_icon_pause");
	app->spriteManager->Load("resources\\sprites\\gui\\gui_mm_logo.sprite", "g_mm_logo");
	app->spriteManager->Load("resources\\sprites\\gui\\gui_mm_play.sprite", "g_mm_play");
	app->spriteManager->Load("resources\\sprites\\gui\\white_quad.sprite", "g_white");

	app->spriteManager->Load("resources\\sprites\\gui\\gui_fail_logo.sprite", "g_fail_logo");
	app->spriteManager->Load("resources\\sprites\\gui\\gui_icon_house.sprite", "g_icon_house");
	app->spriteManager->Load("resources\\sprites\\gui\\gui_icon_retry.sprite", "g_icon_retry");
}

void CGame::LoadFonts()
{
	app->fontManager->Load("resources\\fonts\\arial.ttf", "Arial");
	app->fontManager->Load("resources\\fonts\\utsaah.ttf", "Utsaah1");
	app->fontManager->Load("resources\\fonts\\utsaah.ttf", "Utsaah2");
	app->fontManager->Load("resources\\fonts\\utsaah.ttf", "Utsaah3");
}

//////////////////////////////////////////////////////////////////////////////////////////

void CGame::PlayerFail()
{
	gInterface->HideGameHUD();
	gInterface->ShowFailMenu();
}

// CALLBACKS
void CGame::onGameStateChange(IState *newState, IState *oldState)
{
	if(newState == state->StateGame)
	{
		if(oldState == state->StateFail)
		{
			gInterface->HideFailMenu();
			//level->Restart();
		}
		else
		{
			level->Start();
			gInterface->ShowGameHUD();
		}
	}
	else if(newState == state->StateLoadingResources)
	{
		LoadResources();

		ShowDebugInfo();

		state->DispatchEvent(ON_RESOURCES_LOADED);
	}
	else if(newState == state->StateLoadingImage)
	{
		gInterface->ShowLoadingImage();
	}
	else if(newState == state->StateMainMenu)
	{
		gInterface->ShowMainMenu(oldState);
		level->Create();
	}
	else if(newState == state->StateStarting)
	{
		gInterface->HideMainMenu();
	}
	/*else if(newState == state->StateFail)
	{
		PlayerFail();
	}*/
}

void CGame::onObjectCollision(PlatformEngine::CContact *Contact)
{
	if(state->GetState() == state->StateGame)
	{
		if(Contact->object1 == GetLevel()->GetPlayer()->GetObjectID())
		{
			if(Contact->direction != DIRECTION_HORIZONTAL)
			{
				// Проебал
				state->DispatchEvent(ON_PLAYER_FAIL);
			}
			else
			{
				if(Contact->overlapY < 0)
				{
					state->DispatchEvent(ON_PLAYER_FAIL);
				}
				else level->oldPosCheck = true;
			}
		}
	}
}

void CGame::LoopFunction()
{
	state->GetState()->LoopFunction();
}

void CGame::onKeyDown(int key)
{

}

void CGame::onKeyUp(int key)
{
	
}

void CGame::onMouseDown(int button, int x, int y)
{

}

void CGame::onMouseUp(int button, int x, int y)
{

}

void CGame::onMouseMove(int x, int y)
{

}