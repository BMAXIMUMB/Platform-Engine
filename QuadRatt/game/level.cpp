// level.cpp

#include "level.h"
#include "entity.h"

CLevel::CLevel(PE::CWorld *world, PE::CApplication *app)
{
	this->world = world;
	this->app = app;

	background = new CBackground(world);
	player = new CPlayer;
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
	background->Create(app);
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

	printf("Loaded barrier pattern: %s\n", filename);
	binfo->LoadFromFile(path, app->spriteManager);

	return binfo;
}

void CLevel::BarrierGenerate(float offset)
{
	CBarrier *b = new CBarrier;

	b->Create(world, barrierInfoList[RandomValue(0, barrierInfoList.size())], offset);
	barrierList.push_back(b);
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

void CLevel::BarrierCheck()
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
	background->Check(world->camera, app);
}

void CLevel::PlayerCreate()
{
	entitysettings es;

	es.spawnPosX = START_PLAYER_POSX;
	es.spawnPosY = START_PLAYER_POSY;
	es.sizeX = 64.0f;
	es.sizeY = 64.0f;
	es.sprite = app->spriteManager->Get("s_player");
	es.color = {RGB256(255), RGB256(255), RGB256(255), RGB256(255)};
	
	GetPlayer()->Create(world, es);
	GetPlayer()->Spawn();
	GetPlayer()->Move(750.0, OBJECT_CURRENT_VALUE);

	world->camera->AttachToObject(GetPlayer()->GetObjectID(), -200.0f, 0.0f, 0.0f, 376.0f);
}

void CLevel::Start()
{
	LoadBarrierInfo();
	PlayerCreate();
	CreateBackground();
	BarrierGenerate(START_BARRIER_OFFSET);
}

void CLevel::Update()
{
	CheckBackground();
	BarrierCheck();
}