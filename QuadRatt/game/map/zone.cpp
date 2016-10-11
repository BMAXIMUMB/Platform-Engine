// zone.cpp

#include "map.h"

#include "zone.h"

IZone::IZone(ZoneInfo zi)
{
	map = zi.map;
	beginPos = zi.beginPos;
	prevZoneID = zi.lastZoneID;

	isCreated = false;
}

IZone::~IZone()
{

}


//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------


TowerHole::TowerHole(ZoneInfo zi) :IZone(zi)
{
	lenght = RandomValue(1300, 1700);

	lastTowerType = TowerType::Null;
}

TowerHole::~TowerHole()
{

}

void TowerHole::Generate()
{
	float posX = 0.0f;
	float posY = 0.0f;

	int rndVal = RandomValue(0, 5);

	switch(rndVal)
	{
		case 0:	// 1 тип башни
		case 1:
		case 2:
		{
			posX = map->GetMapEnd() + restTowerDistance;

			posY = restGroundLevel;
			map->CreateBlock(posX, posY);
			
			posY = restGroundLevel + (restBlockSize);
			map->CreateBlock(posX, posY);
			
			posY = restGroundLevel + (restBlockSize * 3) + restMoreHoleSize;
			map->CreateBlock(posX, posY);

			/*if(RandomValue(0, 1) == 0)
			{
			CEntity *object2;

			spawnPosX = spawnPosX + (blockSize*2);
			spawnPosY = groundLevel;

			object2 = new CBlock(world);
			object2->Create(spawnPosX, spawnPosY);
			objectList.push_back(object2);
			}*/

			lastTowerType = TowerType::Type1;
		}
		break;

		case 3:
		case 4:
		{
			if(lastTowerType != TowerType::Type3)
			{
				//--------------------------------------------
				posX = map->GetMapEnd() + restTowerDistance - (64 * 4);
				posY = restGroundLevel;

				map->CreateBlock(posX, posY);
				//--------------------------------------------
				if(lastTowerType == TowerType::Type2) posX = map->GetMapEnd() + restTowerDistance;
				else posX = map->GetMapEnd() + restTowerDistance - 64;
			}
			else
			{
				//--------------------------------------------
				posX = map->GetMapEnd() + restTowerDistance - (64 * 2);
				posY = restGroundLevel;

				map->CreateBlock(posX, posY);
				//--------------------------------------------
				posX = map->GetMapEnd() + restTowerDistance + (64 * 2);
			}

			map->CreateBlock(posX, posY);

			posY = restGroundLevel + (restBlockSize);
			map->CreateBlock(posX, posY);
			
			posY = restGroundLevel + (restBlockSize * 2);
			map->CreateBlock(posX, posY);

			posY = restGroundLevel + (restBlockSize * 4) + restMoreHoleSize;
			map->CreateBlock(posX, posY);

			lastTowerType = TowerType::Type2;
		}
		break;

		case 5: // 3 тип башни
		{
			posX = map->GetMapEnd() + restTowerDistance;

			posY = restGroundLevel + restBlockSize + restMoreHoleSize;
			map->CreateBlock(posX, posY);
			
			posY = restGroundLevel + (restBlockSize * 2) + restMoreHoleSize;
			map->CreateBlock(posX, posY);
		
			posY = restGroundLevel + (restBlockSize * 3) + restMoreHoleSize;
			map->CreateBlock(posX, posY);
			

			lastTowerType = TowerType::Type3;
		}
		break;

	}

	if(!isCreated) isCreated = true;
	map->SetMapEnd(posX);
}

//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------

TowerStairs::TowerStairs(ZoneInfo zi) :IZone(zi)
{
	lenght = RandomValue(3700, 5000);

	lastHoleLevel = -1;
}

TowerStairs::~TowerStairs()
{

}

void TowerStairs::Generate()
{
	int level = 0;

	if(!isCreated)	// Если ни одна башня еще не создана
	{
		// Зададим начальный уровень пролета (1, 2)
		level = RandomValue(1, 2);

		isCreated = true;
	}
	else
	{
		int direction;	// Направление лестницы ( 0 - вниз, 1 - вверх)

		// Выберем, куда будет строиться лестница (вверх или вниз)

		if(lastHoleLevel == 1) direction = 1;
		else direction = RandomValue(0, 1);

		// Определим высоту следующего пролета

		if(lastHoleLevel == 2 && direction == 0) level = 1;
		else level = RandomValue(1, 2);
		
		if(direction == 1 && lastHoleLevel+level < 7) level += lastHoleLevel;
		else level = lastHoleLevel - level;

	}
	// Создадим башню
	TowerCreate(level);
}

void TowerStairs::TowerCreate(int holeLevel)
{
	float posY = 0.0f;
	float posX = 0.0f;
	int offset = 0;

	switch(holeLevel - lastHoleLevel)
	{
		case 1:
			offset = 4;
			break;

		case 2:
			offset = 3;
			break;

		case -1:
			offset = 3;
			break;

		case -2:
			offset = 3;
			break;

		case 0:
			offset = 4;
			break;

		default: offset = 4;
	}
	if(lastHoleLevel == -1) posX = map->GetMapEnd() + restZoneDistance;

	/**
	*	TODO:
	*	Если не прибавить 8, проходить будет очень сложно
	*	или даже не возможно. Нужно тестить и править физику
	*	если нужно
	*/
	else posX = map->GetMapEnd() + (restBlockSize*offset) + 5;

	for(int i = 0; i < restTowerHeight; i++)
	{
		if(i < holeLevel)
		{
			posY = restGroundLevel + (restBlockSize*i);
		}
		else
		{
			posY = restGroundLevel + (restBlockSize*(i + restHoleSize));
		}
		map->CreateBlock(posX, posY);
	}

	lastHoleLevel = holeLevel;
	map->SetMapEnd(posX);
}

//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------

PlatformStairs::PlatformStairs(ZoneInfo zi) : IZone(zi)
{
	int stage = RandomValue(10, 17);
	logprintf("stage %d", stage);
	lenght = stage * (int)(restStageDistance*restMiniPlatformSize);

	lastLevel = -1;
}

PlatformStairs::~PlatformStairs()
{

}

void PlatformStairs::Generate()
{
	float posX = 0.0f;
	float posY = 0.0f;

	int direction=1;	// Направление лестницы ( -1 - вниз, 0 - никуда, 1 - вверх)

	if(lastLevel == -1)
	{
		posY = restStartPosY;
		lastLevel = 0;
	}
	else
	{
		if(direction) posY = restStartPosY + ((++lastLevel)*restBlockSize);
	}

	posX = map->GetMapEnd() + (restStageDistance*restMiniPlatformSize);

	map->CreateMiniPlatform(posX, posY);

	if(!isCreated) isCreated = true;
	map->SetMapEnd(posX);
}