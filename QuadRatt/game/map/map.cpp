// map.cpp

#include "map.h"

CMap::CMap(PlatformEngine::CWorld *world)
{
	this->world = world;

	mapEnd = 0.0f;
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

void CMap::Check()
{
	float cpos[2];
	int wsize[2];

	// Узнаем позицию камеры и размеры экрана
	world->camera->GetPosition(cpos[0], cpos[1]);
	world->GetApp()->GetWindowSize(wsize[0], wsize[1]);
	
	// Определяем, нужно ли сгенерировать новые объекты
	if(mapEnd < cpos[0] - world->camera->offsetX + (wsize[0] / 2))
	{
		mapGenerator->Generate(objectList, mapEnd);
	}

	// Определяем, нужно ли удалить объекты, ушедшие за левую часть экрана

	float pos[2];
	float size[2];

	for(unsigned int i = 0; i < objectList.size(); i++)
	{
		objectList[i]->GetPosition(pos[0], pos[1]);
		objectList[i]->GetSize(size[0], size[1]);

		if(pos[0] + size[0] < cpos[0] - (wsize[0] / 2))
		{
			// Удаляем
			delete objectList[i];
			objectList.erase(objectList.begin() + i);
			break;
		}
	}
}

void CMap::SetGeneratePos(float position)
{
	mapEnd = position;
}