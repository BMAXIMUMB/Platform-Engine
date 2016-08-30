// map_generator.cpp

#include "map_generator.h"

CMapGenerator::CMapGenerator(PlatformEngine::CWorld *world)
{
	this->world = world;
	lastZoneID = -1;
}

CMapGenerator::~CMapGenerator()
{

}

void CMapGenerator::Reset()
{
	if(currentZone != nullptr)
	{
		delete currentZone;
		currentZone = nullptr;
	}
}

void CMapGenerator::Generate(std::vector<CEntity*> &objectList, float &mapEnd)
{
	if(currentZone == nullptr || currentZone->beginPos + currentZone->lenght < mapEnd)
	{
		if(currentZone != nullptr) delete currentZone;
		currentZone = CreateZone(mapEnd);
	}

	currentZone->Generate(objectList, mapEnd);
}

IZone* CMapGenerator::CreateZone(float beginPos)
{
	IZone *zone;
	int rndVal;

	// Не допускаем генерацию 2-х одинаковых зон друг за другом
	bool loop = true;
	while(loop)
	{
		rndVal = RandomValue(0, 1);
		if(rndVal != lastZoneID) loop = false;
	}

	switch(rndVal)
	{
		case 0:
			zone = new TowerStairs(world, (int)beginPos);
			break;

		case 1:
			zone = new TowerHole(world, (int)beginPos);
			break;
	}
	lastZoneID = rndVal;
	
	// DEBUG
	logprintf("created zone \"%s\"", typeid(*zone).name());

	return zone;
}