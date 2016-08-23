// level.cpp

#include "level.h"
#include "entity.h"
#include "game.h"
#include "gamegui.h"

//----------------------------------------------------------------------------------------------------------

CLevel::CLevel(CGame *game)
{
	this->game = game;
	this->world = game->GetWorld();
	this->app = game->GetApp();

	background = new CBackground(world);
	map = new CMap(world);
}

CLevel::~CLevel()
{
	delete background;
	delete player;
}

CBackground* CLevel::GetBackground(void)
{
	return background;
}

CPlayer* CLevel::GetPlayer(void)
{
	return player;
}

void CLevel::CreateBackground()
{
	background->Create();
}

void CLevel::CheckBackground()
{
	background->Check();
}

void CLevel::CheckMap()
{
	map->Check();
}

void CLevel::Check()
{
	CheckMap();
	//CheckBarrier();
}

void CLevel::PlayerCreate()
{
	player = new CPlayer(world);

	GetPlayer()->Create(START_PLAYER_POSX, START_PLAYER_POSY);
	GetPlayer()->Spawn();
	GetPlayer()->Move(700.0, OBJECT_CURRENT_VALUE);

	world->camera->AttachToObject(GetPlayer()->GetObjectID(), -200.0f, 0.0f, 0.0f, 376.0f);
}

void CLevel::Create()
{
	// Создаем фон 
	CreateBackground();

	// Создаем игрока
	PlayerCreate();
}

void CLevel::Destroy()
{

}

void CLevel::Start()
{
	player->SetStartPos();

	// Изменяем стратовую позицию генерации карты
	float pos[2];
	player->GetPosition(pos[0], pos[1]);
	map->SetGeneratePos(START_BARRIER_OFFSET + pos[0]);
}

void CLevel::Restart()
{
	game->GetInterface()->HideFailMenu();
	
	// Перемещаем игрока в стартовую позицию, задаем скорость
	player->Respawn();

	map->Clear();
	map->SetGeneratePos(START_BARRIER_OFFSET);

	background->Reset();
}

void CLevel::LoopFunction()
{
	CheckBackground();

	float pos[2];
	player->GetPosition(pos[0], pos[1]);

	// Костыль для увеличения скорости падения игрока в объекта
	if(oldPosCheck)
	{
		if(pos[1] < oldPosX)
		{
			player->Move(OBJECT_CURRENT_VALUE, -500.0f);
			oldPosCheck = false;
		}
		else if(pos[1] > oldPosX) oldPosCheck = false;
	}
	

	oldPosX = pos[1];
}