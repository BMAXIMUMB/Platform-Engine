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

	world			= new PE::CWorld(App, ws);
	gInterface		= new CInterface(this);
	debugInfo		= new CDebug(App);


	world->physics->SetGravity(GRAVITY_DEFAULT);
	world->SetCollisionFunction(OnObjCollision);
	SetState(GAME_STATE_LOADING_IMAGE);

	level = nullptr;
}

CGame::~CGame()
{
	if(level != nullptr) delete level;

	delete world;
	delete gInterface;
	delete debugInfo;
}

void CGame::ShowDebugInfo()
{
	debugInfo->ShowDebugInfo();
}

gamestate CGame::GetState()
{
	return state.top();
}

void CGame::SetState(gamestate _gamestate)
{
	gamestate tempgs = (state.empty() ? GAME_STATE_NO : GetState());

	state.push(_gamestate);
	onGameStateChange(_gamestate, tempgs);
}

void CGame::DownState()
{
	gamestate gs = GetState();

	state.pop();
	onGameStateChange(GetState(), gs);
}

void CGame::Start()
{
	SetState(GAME_STATE_GAME);

	level->Start();
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
	app->spriteManager->Load("resources\\sprites\\gui\\button_play.sprite", "mm_button_play");
	app->spriteManager->Load("resources\\sprites\\gui\\logo.sprite", "mm_logo");
	app->spriteManager->Load("resources\\sprites\\gui\\mm_bg.sprite", "mm_background");
}

void CGame::LoadFonts()
{
	app->fontManager->Load("resources\\fonts\\arial.ttf", "Arial");
	app->fontManager->Load("resources\\fonts\\arial.ttf", "Arial2");
}

//////////////////////////////////////////////////////////////////////////////////////////

void CGame::PlayerFail()
{

}

// CALLBACKS
void CGame::onGameStateChange(gamestate newgs, gamestate oldgs)
{
	if(newgs == GAME_STATE_GAME)
	{
		level = new::CLevel(world, app);

		level->Start();

		ShowDebugInfo();

		gInterface->ShowGameHUD();
	}
	else if(newgs == GAME_STATE_LOAD_RESOURCES)
	{
		LoadResources();
		SetState(GAME_STATE_MAIN_MENU);
	}
	else if(newgs == GAME_STATE_LOADING_IMAGE)
	{
		gInterface->ShowLoadingImage();
	}
	else if(newgs == GAME_STATE_MAIN_MENU)
	{
		gInterface->ShowMainMenu(oldgs);
	}
	else if(newgs == GAME_STATE_STARTING)
	{
		gInterface->HideMainMenu();
	}
}

void CGame::onObjectCollision(PE::CContact *Contact)
{
	if(Contact->object1 == GetLevel()->GetPlayer()->GetObjectID())
	{
		if(Contact->routPush != ROUT_PUSH_Y)
		{
			
		}
	}
}

void CGame::LoopFunction()
{
	if(GetState() == GAME_STATE_GAME)
	{
		level->Update();
		DebugInfoUpdate();
		level->GetPlayer()->UpdateScore();
		gInterface->UpdatePlayerScore();
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