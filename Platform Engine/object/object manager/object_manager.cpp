// object manager.cpp

#include "object_manager.h"

namespace PlatformEngine
{
	ObjectManager::ObjectManager()
	{
		
	}

	ObjectManager::~ObjectManager()
	{

	}

	void ObjectManager::Update(float dTime)
	{
		for(unsigned int i = 0; i < DrawObject.size(); i++)		// Пробегаемся по всем объектам в списке
		{
			if(DrawObject[i]->GetObjectType() == OBJECT_TYPE_DYNAMIC) DrawObject[i]->Update(dTime);
		}
	}

	/*void ObjectManager::CollisionUpdate()
	{
		// Проверка столкновений
		float objpos[4], objsize[4];
		for(unsigned int i = 0; i < DrawObject.size(); i++)
		{
			// Если объект динамический, чекнем его
			if(DrawObject[i]->GetObjectType() == OBJECT_TYPE_DYNAMIC)
			{
				// Узнаем позицию объекта и вычисляем граничные точки
				DrawObject[i]->GetPosition(objpos[0], objpos[1]);
				DrawObject[i]->GetSize(objsize[0], objsize[1]);
				objpos[0] -= objsize[0] / 2;
				objpos[1] -= objsize[1] / 2;
				for(unsigned int k = 0; k < DrawObject.size(); k++)
				{
					// Если динамический объект != проверяемому
					if(DrawObject[i] != DrawObject[k])
					{
						// Узнаем позиции объектов
						DrawObject[k]->GetPosition(objpos[2], objpos[3]);
						DrawObject[k]->GetSize(objsize[2], objsize[3]);
						// Вычисляем граничные точки
						objpos[2] -= objsize[2] / 2;
						objpos[3] -= objsize[3] / 2;
						// Проверяем, столкнулись ли объекты 
						if(objpos[0] + objsize[0] >= objpos[2] && objpos[0] <= objpos[2] + objsize[2] &&
							objpos[1] + objsize[1] >= objpos[3] && objpos[1] <= objpos[3] + objsize[3])
						{
							// Если да, создаем событие Contact
							printf("COLL\n");
						}
					}
				}
			}
		}
	}*/

	void ObjectManager::Draw(Application *app, Camera *Cam)
	{
		for(unsigned int i = 0; i < DrawObject.size(); i++)		// Пробегаемся по всем объектам в списке
		{
			float objinfo[5];
			DrawObject[i]->GetPosition(objinfo[0], objinfo[1]);
			DrawObject[i]->GetSize(objinfo[2], objinfo[3]);
			objinfo[4] = DrawObject[i]->GetRotate();
			DrawObject[i]->sprite->Draw(app, objinfo[0], objinfo[1], objinfo[2], objinfo[3], objinfo[4], Cam);	// Рисуем каждый объект
		}
	}

	void ObjectManager::ObjectAdd(Object *Object)
	{
		DrawObject.push_back(Object);
	}

	void ObjectManager::ObjectDelete(Object *Object)
	{
		for(unsigned int i = 0; i < DrawObject.size(); i++)
		{
			if(DrawObject[i] == Object)
			{
				DrawObject.erase(DrawObject.begin() + i);
			}
		}
	}

	void ObjectManager::Clear()
	{
		DrawObject.clear();
	}
};