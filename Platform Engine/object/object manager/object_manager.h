// object manager.h

#ifndef ___object_manager_h___
#define ___object_manager_h___

#include <vector>
#include "../object.h"
#include "../../world/camera/camera.h"

namespace PlatformEngine
{
	class ObjectManager
	{
		friend World;
	private:
		std::vector< PlatformEngine::Object*> DrawObject;				// Тут хранятся все объекты на отрисовку
		std::vector< PlatformEngine::Object*> ColObject;				// Объекты, проверяемые на столкновения
	public:
		ObjectManager();
		~ObjectManager();
		void Draw(Application *app, Camera *Cam);						// Отрисовать все объекты
		void Update(float dTime);										// Обновить все объекты в списке
		//void CollisionUpdate(void);										// Проверка столкновений
		void ObjectAdd(Object *Object);
		void ObjectDelete(Object *Object);
		void Clear(void);												// Очистить список объектов
	};
};

#endif //___oject_manager_h___