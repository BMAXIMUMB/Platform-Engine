// zone.cpp

#include "zone.h"

IZone::IZone(PlatformEngine::CWorld *world, int beginPos)
{
	this->world = world;
	this->beginPos = beginPos;
}

IZone::~IZone()
{

}


//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------


TowerHole::TowerHole(PlatformEngine::CWorld *world, int beginPos) :IZone(world, beginPos)
{
	lenght = RandomValue(1300, 1700);
	lastTowerType = Null;
}

TowerHole::~TowerHole()
{

}

void TowerHole::Generate(std::vector<CEntity*> &objectList, float &mapEnd)
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
			CEntity *object[3];

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

			objectList.push_back(object[0]);
			objectList.push_back(object[1]);
			objectList.push_back(object[2]);

			lastTowerType = Type1;
		}
		break;

		case 3:
		case 4:
		{
			CEntity *object[5];
			if(lastTowerType != Type3)
			{
				//--------------------------------------------
				posX = mapEnd + restTowerDistance - (64 * 4);
				posY = restGroundLevel;

				object[4] = new CBlock(world);
				object[4]->Create(posX, posY);
				//--------------------------------------------
				if(lastTowerType == Type2) posX = mapEnd + restTowerDistance;
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

			objectList.push_back(object[0]);
			objectList.push_back(object[1]);
			objectList.push_back(object[2]);
			objectList.push_back(object[3]);
			objectList.push_back(object[4]);

			lastTowerType = Type2;
		}
		break;

		case 5: // 3 тип башни
		{
			CEntity *object[3];

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

			objectList.push_back(object[0]);
			objectList.push_back(object[1]);
			objectList.push_back(object[2]);

			lastTowerType = Type3;
		}
		break;

	}

	mapEnd = posX;

	logprintf("generate");
}

//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------

TowerStairs::TowerStairs(PlatformEngine::CWorld *world, int beginPos) :IZone(world, beginPos)
{
	lenght = RandomValue(3700, 5000);
	isCreated = false;
}

TowerStairs::~TowerStairs()
{

}

void TowerStairs::Generate(std::vector<CEntity*> &objectList, float &mapEnd)
{
	float posX = 0.0f;
	float posY = 0.0f;

	if(!isCreated)	// Если ни одна башня еще не создана
	{
		// Зададим начальный уровень пролета (1, 2)
		int level = RandomValue(1, 2);

		CEntity *object[7];

		//--------------------------------------------
		posX = mapEnd + restTowerDistance;
		posY = restGroundLevel;

		object[0] = new CBlock(world);
		object[0]->Create(posX, posY);
		//--------------------------------------------
		if(level == 2)
		{
			posY = restGroundLevel + restBlockSize;
			CEntity *obj = new CBlock(world);
			obj->Create(posX, posY);
			objectList.push_back(obj);
		}

		for(int i = 1; i < 7; i++)
		{
			posY = restGroundLevel + (level+(i-1)+ holeSize)*restBlockSize;

			object[i] = new CBlock(world);
			object[i]->Create(posX, posY);
		}

		lastHoleLevel = level;

		for(int i = 0; i < _countof(object); i++) objectList.push_back(object[i]);

		mapEnd = posX;

		isCreated = true;
	}
	else
	{
		int direction;	// Направление лестницы ( 0 - вниз, 1 - вверх)
		int level;

		// Выберем, куда будет строиться лестница (вверх или вниз)

		if(lastHoleLevel == 1) direction = 1;
		else direction = RandomValue(0, 1);

		// Определим высоту следующего пролета

		if(lastHoleLevel == 2 && direction == 0) level = 1;
		else level = RandomValue(1, 2);
		
		if(direction == 1) level += lastHoleLevel;
		else level = lastHoleLevel - level;
		
		CEntity *object[7];

		posX = mapEnd + restTowerDistance;
		posY = restGroundLevel;
		//--------------------------------------------
		posX = mapEnd + restTowerDistance;
		posY = restGroundLevel;

		object[0] = new CBlock(world);
		object[0]->Create(posX, posY);
		//--------------------------------------------
	}
}

void TowerStairs::TowerCreate(int holeLevel)
{

}