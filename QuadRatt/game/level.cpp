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
	player = new CPlayer;
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

void CLevel::LoadBarrierInfo()
{
	// Ищем все файлы в папке с шаблонами препятствий
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;

	hf = FindFirstFile(BINFO_PATH BINFO_MASK, &FindFileData);

	if(hf != INVALID_HANDLE_VALUE)
	{
		do
		{
			barrierInfoList.push_back(LoadBarrierInfoFromFile(FindFileData.cFileName));
		}
		while(FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}
}

CBarrierInfo* CLevel::LoadBarrierInfoFromFile(const char *filename)
{
	CBarrierInfo *binfo = new CBarrierInfo;

	char path[100] = BINFO_PATH;
	strcat(path, filename);

	logprintf("Loaded barrier pattern: %s", filename);
	binfo->LoadFromFile(path, app->spriteManager);

	return binfo;
}

void CLevel::StartBarrierGenerate(void)
{
	float pos[2];
	player->GetPosition(pos[0], pos[1]);

	BarrierGenerate(START_BARRIER_OFFSET + pos[0]);
}

void CLevel::BarrierGenerate(float offset)
{
	CBarrier *b = new CBarrier;

	b->Create(world, barrierInfoList[RandomValue(0, barrierInfoList.size())], offset);
	barrierList.push_back(b);
}

void CLevel::BarrierAllDelete()
{
	for(auto it = barrierList.begin(); it != barrierList.end(); it++)
	{
		delete (*it);
	}

	barrierList.clear();
}

void CLevel::BarrierDelete(CBarrier *Barrier)
{
	for(auto it = barrierList.begin(); it != barrierList.end(); it++)
	{
		if(*it == Barrier)
		{
			barrierList.erase(it);
			delete Barrier;
			break;
		}
	}
}

void CLevel::CheckBarrier()
{
	// Тут мы чекаем, нужно ли создать новое препятствие или удалить старое
	// Сначала узнаем позицию камеры и размеры экрана
	float cpos[2];
	int wsize[2];

	world->camera->GetPosition(cpos[0], cpos[1]);
	app->GetWindowSize(wsize[0], wsize[1]);
	
	// Узнаем длину препятствия и ее сдвиг
	CBarrier *barrier_back = barrierList.back();

	float boffset = barrier_back->GetOffset();
	float bsize = barrier_back->GetSize();

	if(boffset + bsize < cpos[0] - world->camera->offsetX + (wsize[0] / 2))
	{
		BarrierGenerate(boffset + bsize);
	}

	CBarrier *barrier_front = barrierList.front();

	boffset = barrier_front->GetOffset();
	bsize = barrier_front->GetSize();

	if(boffset + bsize < cpos[0] - (wsize[0] / 2))
	{
		BarrierDelete(barrier_front);
	}
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
	CheckBarrier();
}

void CLevel::PlayerCreate()
{
	entitysettings es;

	es.spawnPosX = START_PLAYER_POSX;
	es.spawnPosY = START_PLAYER_POSY;
	es.sizeX = 64.0f;
	es.sizeY = 64.0f;
	es.sprite = app->spriteManager->Get("s_player");
	es.color = 0xffffffff;
	
	GetPlayer()->Create(world, es);
	GetPlayer()->Spawn();
	GetPlayer()->Move(750.0, OBJECT_CURRENT_VALUE);

	world->camera->AttachToObject(GetPlayer()->GetObjectID(), -200.0f, 0.0f, 0.0f, 376.0f);
}

void CLevel::Create()
{
	// Создаем уровень
	// Загружаем инфу о препядствиях
	LoadBarrierInfo();

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
	StartBarrierGenerate();
	player->SetStartPos();
}

void CLevel::Restart()
{
	game->GetInterface()->HideFailMenu();
	
	// Перемещаем игрока в стартовую позицию, задаем скорость
	player->Respawn();

	// Удаляем препятствия и генерируем новые
	BarrierAllDelete();
	StartBarrierGenerate();

	background->Reset();
}

void CLevel::LoopFunction()
{
	CheckBackground();
}