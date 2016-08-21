// map_generator.cpp

#include "map_generator.h"

CMapGenerator::CMapGenerator(PlatformEngine::CWorld *world)
{
	this->world = world;

	currentZone = nullptr;
}

CMapGenerator::~CMapGenerator()
{

}

void CMapGenerator::Generate(std::vector<CEntity*> &objectList, float &mapEnd)
{
	if(currentZone == nullptr || currentZone->beginPos + currentZone->lenght < mapEnd)
	{
		// DEBUG
		logprintf("delete zone");
		
		if(currentZone != nullptr) delete currentZone;
		currentZone = CreateZone(mapEnd);
	}

	currentZone->Generate(objectList, mapEnd);
}

IZone* CMapGenerator::CreateZone(float beginPos)
{
	IZone *zone;
	int rndVal = RandomValue(0, 1);

	switch(rndVal)
	{
		case 0:
			zone = new SimpleZone(world, (int)beginPos);
			break;

		case 1:
			zone = new SimpleZone(world, (int)beginPos);
			break;
	}
	
	// DEBUG
	logprintf("created zone \"%s\"", typeid(*zone).name());

	return zone;
}