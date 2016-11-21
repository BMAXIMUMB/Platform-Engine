// map_generator.cpp

#include "map.h"
#include "map_generator.h"

CMapGenerator::CMapGenerator(CMap* map)
{
	this->map = map;
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

void CMapGenerator::Generate()
{
	if(currentZone == nullptr || currentZone->beginPos + currentZone->lenght < map->GetMapEnd())
	{
		if(currentZone != nullptr) delete currentZone;
		currentZone = CreateZone();
	}

	currentZone->Generate();
}

IZone* CMapGenerator::CreateZone()
{
	IZone *zone;
	int rndVal;

	// Не допускаем генерацию 2-х одинаковых зон друг за другом
	bool loop = true;
	while(loop)
	{
		rndVal = RandomValue(0, 2);
		if(rndVal != lastZoneID) loop = false;
	}

	ZoneInfo zoneInfo;
	zoneInfo.beginPos = (int)map->GetMapEnd();
	zoneInfo.lastZoneID = lastZoneID;
	zoneInfo.map = map;

	switch(rndVal)
	{
		/*case 0:
			zone = new TowerStairs(zoneInfo);
			break;

		case 1:
			zone = new TowerHole(zoneInfo);
			break;

		case 2:
			zone = new PlatformStairs(zoneInfo);
			break;*/
		default: zone = new ShortThorns(zoneInfo);
	}
	lastZoneID = rndVal;
	
	// DEBUG
	logprintf("created zone \"%s\"", typeid(*zone).name());

	return zone;
}