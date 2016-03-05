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

	world			= new PE::CWorld(app, ws);
	level			= new CLevel(this);
	gInterface		= new CInterface(this);
	debugInfo		= new CDebug(app);
	state			= new CGameState(this);


	world->physics->SetGravity(GRAVITY_DEFAULT);
	world->SetCollisionFunction(OnObjCollision);

	SetState(GAME_STATE_LOADING_IMAGE);
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

enGameState CGame::GetState()
{
	return state->Get();
}

void CGame::SetState(enGameState gameState)
{
	state->Set(gameState);
}

void CGame::Start()
{
	SetState(GAME_STATE_GAME);
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
void CGame::onGameStateChange(enGameState newgs, enGameState oldgs)
{
	if(newgs == GAME_STATE_GAME)
	{
		if(oldgs == GAME_STATE_FAIL)
		{
			gInterface->HideFailMenu();
			level->Restart();
		}
		else
		{
			level->Start();
			gInterface->ShowGameHUD();
		}
	}
	else if(newgs == GAME_STATE_LOAD_RESOURCES)
	{
		LoadResources();

#ifdef _DEBUG
		ShowDebugInfo();
#endif

		SetState(GAME_STATE_MAIN_MENU);
	}
	else if(newgs == GAME_STATE_LOADING_IMAGE)
	{
		gInterface->ShowLoadingImage();
	}
	else if(newgs == GAME_STATE_MAIN_MENU)
	{
		gInterface->ShowMainMenu(oldgs);
		level->Create();
	}
	else if(newgs == GAME_STATE_STARTING)
	{
		gInterface->HideMainMenu();
	}
	else if(newgs == GAME_STATE_FAIL)
	{
		PlayerFail();
	}
}

void CGame::onObjectCollision(PE::CContact *Contact)
{
	if(GetState() == GAME_STATE_GAME)
	{
		if(Contact->object1 == GetLevel()->GetPlayer()->GetObjectID())
		{
			if(Contact->routPush != ROUT_PUSH_Y)
			{
				SetState(GAME_STATE_FAIL);
			}
		}
	}
}

void CGame::LoopFunction()
{
	if(GetState() == GAME_STATE_GAME)
	{
		level->GetPlayer()->UpdateScore();
		gInterface->UpdatePlayerScore();
	}
	if(GetState() == GAME_STATE_GAME || GetState() == GAME_STATE_MAIN_MENU || GetState() == GAME_STATE_STARTING 
		|| GetState() == GAME_STATE_FAIL)
	{
		DebugInfoUpdate();
		level->Update();
	}
}

void CGame::onKeyDown(int key)
{
	if(GetState() == GAME_STATE_GAME)
	{
		if(key == VK_UP)
		{
			level->GetPlayer()->Jump();
		}
	}
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