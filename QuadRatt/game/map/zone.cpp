// zone.cpp

#include "zone.h"

IZone::IZone(ZoneInfo zi)
{
	world = zi.world;
	beginPos = zi.beginPos;
	prevZoneID = zi.lastZoneID;
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

void TowerHole::Generate(std::vector<IEntity*> &objectList, float &mapEnd)
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
			IEntity *object[3];

			//--------------------------------------------
			posX = mapEnd + restTowerDistance;
			posY = restGroundLevel;

			object[0] = new CBlock(world);
			object[0]->Create(posX, posY);
			//--------------------------------------------
			posY = restGroundLevel + (restBlockSize);

			object[1] = new CBlock(world);
			object[1]->Create(posX, posY);
			//--------------------------------------------
			posY = restGroundLevel + (restBlockSize * 3) + restMoreHoleSize;

			object[2] = new CBlock(world);
			object[2]->Create(posX, posY);
			//--------------------------------------------

			/*if(RandomValue(0, 1) == 0)
			{
			CEntity *object2;

			spawnPosX = spawnPosX + (blockSize*2);
			spawnPosY = groundLevel;

			object2 = new CBlock(world);
			object2->Create(spawnPosX, spawnPosY);
			objectList.push_back(object2);
			}*/
			for(int i = 0; i < _countof(object); i++) objectList.push_back(object[i]);

			lastTowerType = TowerType::Type1;
		}
		break;

		case 3:
		case 4:
		{
			IEntity *object[5];
			if(lastTowerType != TowerType::Type3)
			{
				//--------------------------------------------
				posX = mapEnd + restTowerDistance - (64 * 4);
				posY = restGroundLevel;

				object[4] = new CBlock(world);
				object[4]->Create(posX, posY);
				//--------------------------------------------
				if(lastTowerType == TowerType::Type2) posX = mapEnd + restTowerDistance;
				else posX = mapEnd + restTowerDistance - 64;
			}
			else
			{
				//--------------------------------------------
				posX = mapEnd + restTowerDistance - (64 * 2);
				posY = restGroundLevel;

				object[4] = new CBlock(world);
				object[4]->Create(posX, posY);
				//--------------------------------------------
				posX = mapEnd + restTowerDistance + (64 * 2);
			}

			//--------------------------------------------
			object[0] = new CBlock(world);
			object[0]->Create(posX, posY);
			//--------------------------------------------
			posY = restGroundLevel + (restBlockSize);

			object[1] = new CBlock(world);
			object[1]->Create(posX, posY);
			//--------------------------------------------
			posY = restGroundLevel + (restBlockSize * 2);

			object[2] = new CBlock(world);
			object[2]->Create(posX, posY);
			//--------------------------------------------
			posY = restGroundLevel + (restBlockSize * 4) + restMoreHoleSize;

			object[3] = new CBlock(world);
			object[3]->Create(posX, posY);
			//--------------------------------------------

			for(int i = 0; i < _countof(object); i++) objectList.push_back(object[i]);

			lastTowerType = TowerType::Type2;
		}
		break;

		case 5: // 3 тип башни
		{
			IEntity *object[3];

			//--------------------------------------------
			posX = mapEnd + restTowerDistance;
			posY = restGroundLevel + restBlockSize + restMoreHoleSize;

			object[2] = new CBlock(world);
			object[2]->Create(posX, posY);
			//--------------------------------------------
			posY = restGroundLevel + (restBlockSize * 2) + restMoreHoleSize;

			object[1] = new CBlock(world);
			object[1]->Create(posX, posY);
			//--------------------------------------------
			posY = restGroundLevel + (restBlockSize * 3) + restMoreHoleSize;

			object[0] = new CBlock(world);
			object[0]->Create(posX, posY);
			//--------------------------------------------

			for(int i = 0; i < _countof(object); i++) objectList.push_back(object[i]);

			lastTowerType = TowerType::Type3;
		}
		break;

	}

	mapEnd = posX;
}

//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------

TowerStairs::TowerStairs(ZoneInfo zi) :IZone(zi)
{
	lenght = RandomValue(3700, 5000);

	isCreated = false;
	lastHoleLevel = -1;
}

TowerStairs::~TowerStairs()
{

}

void TowerStairs::Generate(std::vector<IEntity*> &objectList, float &mapEnd)
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
	TowerCreate(level, mapEnd, objectList);
}

void TowerStairs::TowerCreate(int holeLevel, float &mapEnd, std::vector<IEntity*> &objectList)
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
	if(lastHoleLevel == -1) posX = mapEnd + restZoneDistance;
	/**
	*	TODO:
	*	Если не прибавить 8, проходить будет очень сложно
	*	или даже не возможно. Нужно тестить и править физику
	*	если нужно
	*/
	else posX = mapEnd + (restBlockSize*offset) + 8;

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
		IEntity *object = new CBlock(world);
		object->Create(posX, posY);

		objectList.push_back(object);
	}

	lastHoleLevel = holeLevel;
	mapEnd = posX;
}

//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------

PlatformStairs::PlatformStairs(ZoneInfo zi) : IZone(zi)
{
		
}

PlatformStairs::~PlatformStairs()
{

}

void PlatformStairs::Generate(std::vector<IEntity*> &objectList, float &mapEnd)
{
	float posX = 0.0f;
	float posY = 0.0f;
}