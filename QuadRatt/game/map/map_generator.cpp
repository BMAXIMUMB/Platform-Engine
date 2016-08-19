// map_generator.cpp

#include "map_generator.h"

CMapGenerator::CMapGenerator(PlatformEngine::CWorld *world)
{
	this->world = world;

	currentZone = nullptr;

	// test code
	currentZone = new SimpleZone(world);
}

CMapGenerator::~CMapGenerator()
{

}

void CMapGenerator::Generate(std::vector<CEntity*> &objectList, float &mapEnd)
{
	// test code
	currentZone->Generate(objectList, mapEnd);
}