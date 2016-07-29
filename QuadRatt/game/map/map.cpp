// map.cpp

#include "map.h"

CMap::CMap(PlatformEngine::CWorld *world)
{
	this->world = world;

	mapGenerator = new CMapGenerator(world);
}

CMap::~CMap()
{

}

void CMap::Clear()
{
	for(auto it = objectList.begin(); it != objectList.end(); it++)
	{
		delete (*it);
	}

	objectList.clear();
}