// world.h

#ifndef _WORLD_H_
#define _WORLD_H_

#include "physics\physics.h"
#include "physics\contact.h"
#include "camera\camera.h"
#include "../object/object.h"
#include "../object/particles.h"
#include <vector>

//----------------------------------------------------------------------------------------------------------

#define COLLISION_ON								(true)
#define COLLISION_OFF								(false)

struct WorldSettings
{
	bool collision = COLLISION_ON;
	float groundLevel = 0.0f;

	void(*ObjectCollision) (PlatformEngine::CContact*) = nullptr;
};

namespace PlatformEngine
{
	class CApplication;
	class CLayer;

	class CWorld
	{
	private:

		/**
		*	Хранит все объекты мира
		*/
		std::vector< PlatformEngine::CObject*> objectList;

		/**
		*	Источники партиклов
		*/
		std::vector< PlatformEngine::CParticleEmitter*> particleEmitterList;

		/**
		*	Указатель на приложение
		*/
		CApplication *app;

		/**
		*	Включена ли коллизия
		*/
		bool collisionOn;

		/**
		*	Callback
		*/
		void(*ObjectCollision) (CContact*);

	public:

		CPhysics *physics;
		CCamera *camera;
		CLayer *background;

		PLATFORMENGINE_API CWorld(CApplication *app, WorldSettings Settings);
		PLATFORMENGINE_API ~CWorld();

		PLATFORMENGINE_API CWorld* GetID(void);
		PLATFORMENGINE_API CApplication*   GetApp(void);

		/**
		*	Отрисовать мир
		*/
		PLATFORMENGINE_API void Draw();

		/**
		*	Обновить мир
		*/
		PLATFORMENGINE_API void Update(float dTime);

		/**
		*	Включить/отключить столкновения
		*/
		PLATFORMENGINE_API void SetCollision(bool collision);

		/**
		*	Узнать, включены ли столкновения
		*/
		PLATFORMENGINE_API bool GetCollision(void);

		/**
		*	Задать callback столкновений
		*/
		PLATFORMENGINE_API void SetCollisionFunction(void(*ObjectCollision) (CContact*));

		/**
		*	Создать квадратный объект
		*/
		PLATFORMENGINE_API CQuad* CreateObjectQuad(float posX, float posY, float sizeX, float sizeY, CSprite* sprite, int objtype = OBJECT_TYPE_STATIC);

		/**
		*	Удаоить объект
		*/
		PLATFORMENGINE_API void DestroyObject(CObject *Obj);

		/**
		*	Создать источник частиц
		*/
		PLATFORMENGINE_API CParticleEmitter* CreateParticleEmitter(float pos_x, float pos_y, int count, int speed, ParticleEmitterSettings pes, PE::CSprite *Sprite);

		/**
		*	Удалить источник частиц
		*/
		PLATFORMENGINE_API void DestroyParticleEmitter(CParticleEmitter* PS);

		/**
		*	Показать объект
		*/
		PLATFORMENGINE_API void ObjectShow(CObject *Obj);

		/**
		*	Скрыть объект
		*/
		PLATFORMENGINE_API void ObjectHide(CObject *Obj);

		/**
		*	Узнать количество частиц
		*/
		PLATFORMENGINE_API int GetParticleCount(void);

		/**
		*	Обновить частицы
		*/
		void UpdateParticle(float dTime);

		/**
		*	Отрисовать фон
		*/
		void DrawBackground(void);

		/**
		*	Отрисовать частицы
		*/
		void DrawParticle(void);

		/**
		*	Вызывается при обнаружении столкновения
		*/
		void OnObjectCollision(CContact *Contact);

		/**
		*	Добавить объект в список
		*/
		void ObjectAddToList(CObject *Obj);

		/**
		*	Убрать объект из списка
		*/
		bool ObjectDeleteToList(CObject *Obj);

		/**
		*	Добавить источник партиклов в список
		*/
		void PEAddToList(CParticleEmitter *particleEmitter);

		/**
		*	Убрать источник частиц из списка
		*/
		bool PEDeleteToList(CParticleEmitter *particleEmitter);

		/**
		*	Проверка столкновений
		*/
		void CollisionUpdate();
	};
};

#endif //_WORLD_H_