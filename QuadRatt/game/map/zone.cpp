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


SimpleZone::SimpleZone(PlatformEngine::CWorld *world, int beginPos) :IZone(world, beginPos)
{
	lenght = RandomValue(3000, 5000);
}

SimpleZone::~SimpleZone()
{

}

void SimpleZone::Generate(std::vector<CEntity*> &objectList, float &mapEnd)
{
	CEntity *object = new CBlock(world);

	// Генерируем для него позицию
	float spawnPosX = mapEnd + 64*12;
	float spawnPosY = 182;

	object->Create(spawnPosX, spawnPosY);
	objectList.push_back(object);

	/*object = new CBlock(world);
	object->Create(spawnPosX, spawnPosY + 64);
	objectList.push_back(object);*/

	object = new CBlock(world);
	object->Create(spawnPosX+64*2, spawnPosY);
	objectList.push_back(object);
	

	mapEnd = spawnPosX + 64 * 2;

	logprintf("generate");
}
