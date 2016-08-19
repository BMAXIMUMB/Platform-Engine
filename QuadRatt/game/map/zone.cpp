// zone.cpp

#include "zone.h"

IZone::IZone(PlatformEngine::CWorld *world)
{
	this->world = world;
}

IZone::~IZone()
{

}


//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------


SimpleZone::SimpleZone(PlatformEngine::CWorld *world) :IZone(world)
{
	lenght = RandomValue(3000, 5000);
}

SimpleZone::~SimpleZone()
{

}

void SimpleZone::Generate(std::vector<CEntity*> &objectList, float &mapEnd)
{
	// Сначала выделяем память под наш объект
	CEntity *object = new CBlock(world);

	// Генерируем для него позицию
	float spawnPosX = mapEnd + RandomValue(64, 300);
	float spawnPosY = (float)RandomValue(400, 650);

	// Создаем его и пушим в список всех объектов
	object->Create(spawnPosX, spawnPosY);
	objectList.push_back(object);

	mapEnd = spawnPosX;
}
