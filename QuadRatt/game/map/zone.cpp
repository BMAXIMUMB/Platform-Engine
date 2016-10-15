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
	lenght = stage * (int)(restStageDistance*restMiniPlatformSize);

	lastLevel = -1;
	lastDirection = -1;

	directionCounter = 0;
}

PlatformStairs::~PlatformStairs()
{

}

void PlatformStairs::Generate()
{
	float posX = 0.0f;
	float posY = 0.0f;

	// Направление лестницы ( -1 - вниз, 0 - никуда, 1 - вверх)
	int direction;

	// Определим направление лестницы

	bool loop = true;
	while(loop)
	{
		if(lastLevel < 1) direction = RandomValue(0, 1);
		else
		{
			if(directionCounter > 4) direction = RandomValue(-1, 1);
			else
			{
				int values[2] = { -1,1 };
				direction = values[RandomValue(0, 1)];
			}
		}

		if(direction != lastDirection || direction == 1) loop = false;
	}

	if(lastLevel == -1)
	{
		posY = restStartPosY;
		lastLevel = 0;
		lastDirection = -1;
		posX = map->GetMapEnd() + (restStageDistance*restMiniPlatformSize);
	}
	else
	{
		if(direction == 1)
		{
			posY = restStartPosY + ((++lastLevel)*restBlockSize);
			posX = map->GetMapEnd() + (restStageDistance*restMiniPlatformSize);

			directionCounter++;
		}
		else if(direction == -1)
		{
			posY = restStartPosY + ((--lastLevel)*restBlockSize);

			int rndVal = RandomValue(0, 1);
			int multiple[2] = { 3,5 };
			posX = map->GetMapEnd() + (multiple[rndVal] * restMiniPlatformSize);

			directionCounter++;
		}
		else // Если лестница остается на прежнем уровне
		{
			posY = restStartPosY + ((lastLevel)*restBlockSize);
			posX = map->GetMapEnd() + (5 * restMiniPlatformSize);

			directionCounter = 0;
		}
		lastDirection = direction;
	}

	map->CreateMiniPlatform(posX, posY);

	if(!isCreated) isCreated = true;
	map->SetMapEnd(posX);
}