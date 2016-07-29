// map_generator.cpp

#include "map_generator.h"

CMapGenerator::CMapGenerator(PlatformEngine::CWorld *world)
{
	this->world = world;
}

CMapGenerator::~CMapGenerator()
{

}

CEntity* CMapGenerator::CreateObject()
{
	CEntity *object = new CBlock;

	return object;
}

void CMapGenerator::Generate(std::vector<CEntity*> objectList)
{
	
}