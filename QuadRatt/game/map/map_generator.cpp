// map_generator.cpp

#include "map_generator.h"

CMapGenerator::CMapGenerator(PlatformEngine::CWorld *world)
{
	this->world = world;
}

CMapGenerator::~CMapGenerator()
{

}

CEntity* CMapGenerator::CreateObject(float &mapEnd)
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

void CMapGenerator::Generate(std::vector<CEntity*> &objectList, float &mapEnd)
{
	objectList.push_back(CreateObject(mapEnd));
}