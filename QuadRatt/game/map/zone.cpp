// zone.cpp

#include "zone.h"

IZone::IZone(PlatformEngine::CWorld *world)
{
	this->world = world;
}

IZone::~IZone()
{

}

CEntity* IZone::CreateObject(float &mapEnd)
{
	CEntity *object = new CBlock();

	entitysettings es;
	es.spawnPosX = mapEnd + RandomValue(64, 300);
	es.spawnPosY = (float)RandomValue(400, 650);
	es.sizeX = 64;
	es.sizeY = 64;
	es.sprite = world->GetApp()->spriteManager->Get("s_block");

	object->Create(world, es);
	mapEnd = es.spawnPosX;

	return object;
}


//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------


SimpleZone::SimpleZone(PlatformEngine::CWorld *world) :IZone(world)
{

}

SimpleZone::~SimpleZone()
{

}

void SimpleZone::Generate(std::vector<CEntity*> &objectList, float &mapEnd)
{
	objectList.push_back(CreateObject(mapEnd));
}
