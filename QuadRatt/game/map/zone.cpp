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
	float spawnPosX = 0.0f;
	float spawnPosY = 0.0f;

	int rndVal = RandomValue(0, 5);
	switch(rndVal)
	{
		case 0:	// 1 тип башни
		case 1:
		{
			CEntity *object[3];

			//--------------------------------------------
			spawnPosX = mapEnd + restTowerDistance;
			spawnPosY = restGroundLevel;

			object[0] = new CBlock(world);
			object[0]->Create(spawnPosX, spawnPosY);
			//--------------------------------------------
			spawnPosY = restGroundLevel + (restBlockSize);

			object[1] = new CBlock(world);
			object[1]->Create(spawnPosX, spawnPosY);
			//--------------------------------------------
			spawnPosY = restGroundLevel + (restBlockSize * 3) + restMoreHoleSize;

			object[2] = new CBlock(world);
			object[2]->Create(spawnPosX, spawnPosY);
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

		case 2:
		case 3:
		{
			CEntity *object[5];
			if(lastTowerType != Type3)
			{
				//--------------------------------------------
				spawnPosX = mapEnd + restTowerDistance - (64 * 4);
				spawnPosY = restGroundLevel;

				object[4] = new CBlock(world);
				object[4]->Create(spawnPosX, spawnPosY);
				//--------------------------------------------
				if(lastTowerType == Type2) spawnPosX = mapEnd + restTowerDistance;
				else spawnPosX = mapEnd + restTowerDistance - 64;
			}
			else
			{
				//--------------------------------------------
				spawnPosX = mapEnd + restTowerDistance - (64 * 2);
				spawnPosY = restGroundLevel;

				object[4] = new CBlock(world);
				object[4]->Create(spawnPosX, spawnPosY);
				//--------------------------------------------
				spawnPosX = mapEnd + restTowerDistance + (64 * 2);
			}

			//--------------------------------------------
			object[0] = new CBlock(world);
			object[0]->Create(spawnPosX, spawnPosY);
			//--------------------------------------------
			spawnPosY = restGroundLevel + (restBlockSize);

			object[1] = new CBlock(world);
			object[1]->Create(spawnPosX, spawnPosY);
			//--------------------------------------------
			spawnPosY = restGroundLevel + (restBlockSize * 2);

			object[2] = new CBlock(world);
			object[2]->Create(spawnPosX, spawnPosY);
			//--------------------------------------------
			spawnPosY = restGroundLevel + (restBlockSize * 4) + restMoreHoleSize;

			object[3] = new CBlock(world);
			object[3]->Create(spawnPosX, spawnPosY);
			//--------------------------------------------

			objectList.push_back(object[0]);
			objectList.push_back(object[1]);
			objectList.push_back(object[2]);
			objectList.push_back(object[3]);
			objectList.push_back(object[4]);

			lastTowerType = Type2;
		}
		break;

		case 4: // 2 тип башни
		{
			CEntity *object[3];

			//--------------------------------------------
			spawnPosX = mapEnd + restTowerDistance;
			spawnPosY = restGroundLevel + restBlockSize + restMoreHoleSize;

			object[2] = new CBlock(world);
			object[2]->Create(spawnPosX, spawnPosY);
			//--------------------------------------------
			spawnPosY = restGroundLevel + (restBlockSize * 2) + restMoreHoleSize;

			object[1] = new CBlock(world);
			object[1]->Create(spawnPosX, spawnPosY);
			//--------------------------------------------
			spawnPosY = restGroundLevel + (restBlockSize * 3) + restMoreHoleSize;

			object[0] = new CBlock(world);
			object[0]->Create(spawnPosX, spawnPosY);
			//--------------------------------------------

			objectList.push_back(object[0]);
			objectList.push_back(object[1]);
			objectList.push_back(object[2]);

			lastTowerType = Type3;
		}
		break;

	}

	mapEnd = spawnPosX;

	logprintf("generate");
}
