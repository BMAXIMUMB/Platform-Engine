// map.cpp

#include "map.h"

CMap::CMap(PlatformEngine::CWorld *world)
{
	this->world = world;

	mapEnd = 0.0f;
	mapGenerator = new CMapGenerator(this);
	randomDevice = new PlatformEngine::CRandomDevice;
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
	mapGenerator->Reset();
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
		mapGenerator->Generate();
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

float CMap::GetMapEnd()
{
	return mapEnd;
}

//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------

CBlock* CMap::CreateBlock(float posX, float posY)
{
	CBlock *object = new CBlock(world);
	
	object->Create(posX, posY);
	objectList.push_back(object);

	return object;
}

CTriangle* CMap::CreateTriangle(float posX, float posY)
{
	CTriangle *object = new CTriangle(world);

	object->Create(posX, posY);
	objectList.push_back(object);

	return object;
}

CMiniTriangle* CMap::CreateMiniTriangle(float posX, float posY)
{
	CMiniTriangle *object = new CMiniTriangle(world);

	object->Create(posX, posY);
	objectList.push_back(object);

	return object;
}

CMiniPlatform* CMap::CreateMiniPlatform(float posX, float posY)
{
	CMiniPlatform *object = new CMiniPlatform(world);

	object->Create(posX, posY);
	objectList.push_back(object);

	return object;
}

//----------------------------------------------------------------------------------------------------------

bool CMap::DeleteEntity(IEntity* entity)
{
	for(auto it = objectList.begin(); it != objectList.end(); it++)
	{
		if(*it == entity)
		{
			delete entity;
			objectList.erase(it);

			return true;
		}
	}
	return false;
}

bool CMap::DeleteBlock(CBlock *block)
{
	for(auto it = objectList.begin(); it != objectList.end(); it++)
	{
		if(*it == block)
		{
			delete block;
			objectList.erase(it);

			return true;
		}
	}
	return false;
}

bool CMap::DeleteMiniPlatform(CMiniPlatform *object)
{
	for(auto it = objectList.begin(); it != objectList.end(); it++)
	{
		if(*it == object)
		{
			delete object;
			objectList.erase(it);

			return true;
		}
	}
	return false;
}

bool CMap::DeleteTriangle(CTriangle *object)
{
	for(auto it = objectList.begin(); it != objectList.end(); it++)
	{
		if(*it == object)
		{
			delete object;
			objectList.erase(it);

			return true;
		}
	}
	return false;
}

bool CMap::DeleteMiniTriangle(CMiniTriangle *object)
{
	for(auto it = objectList.begin(); it != objectList.end(); it++)
	{
		if(*it == object)
		{
			delete object;
			objectList.erase(it);

			return true;
		}
	}
	return false;
}