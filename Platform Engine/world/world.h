// world.h

#ifndef _WORLD_H_
#define _WORLD_H_

#include "physics\physics.h"
#include "physics\contact.h"
#include "camera\camera.h"
#include "../object/object.h"
#include "../object/particles.h"
#include <vector>

#define COLLISION_ON								(true)
#define COLLISION_OFF								(false)

struct WorldSettings
{
	bool collision										= COLLISION_ON;
	float groundLevel									= 0.0f;

	void(*ObjectCollision) (PlatformEngine::CContact*)	= nullptr;
};

namespace PlatformEngine
{
	class CApplication;
	class CLayer;

	class CWorld
	{
	private:

		// ��� �������� ��� ������� ����
		std::vector< PlatformEngine::CObject*> objectList;
		// ��������� ���������
		std::vector< PlatformEngine::CParticleEmitter*> particleEmitterList;

		CApplication *app;	

		bool collisionOn;

		void(*ObjectCollision) (CContact*);

	public:

		CPhysics *physics;						
		CCamera *camera;
		CLayer *background;

		PLATFORMENGINE_API CWorld(CApplication *app, WorldSettings Settings);
		PLATFORMENGINE_API ~CWorld();

		PLATFORMENGINE_API CWorld* GetID(void);
		PLATFORMENGINE_API CApplication*   GetApp(void);

		PLATFORMENGINE_API void Draw();									// ���������� ���
		PLATFORMENGINE_API void Update(float dTime);					// �������� ���

		PLATFORMENGINE_API void SetCollision(bool collision);			// ��������/��������� ������������
		PLATFORMENGINE_API bool GetCollision(void);						// ������, �������� �� ��������

		PLATFORMENGINE_API void SetCollisionFunction(void(*ObjectCollision) (CContact*));

		PLATFORMENGINE_API CQuad* CreateObjectQuad(float posX, float posY, float sizeX, float sizeY, CSprite* sprite, int objtype = OBJECT_TYPE_STATIC);
		PLATFORMENGINE_API void DestroyObject(CObject *Obj);

		PLATFORMENGINE_API CParticleEmitter* CreateParticleEmitter(float pos_x, float pos_y, int count, int speed, ParticleEmitterSettings pes, PE::CSprite *Sprite);
		PLATFORMENGINE_API void DestroyParticleEmitter(CParticleEmitter* PS);

		PLATFORMENGINE_API void ObjectShow(CObject *Obj);
		PLATFORMENGINE_API void ObjectHide(CObject *Obj);

		PLATFORMENGINE_API int GetParticleCount(void);

		// ���������� ������
		void UpdateParticle(float dTime);
		// ���������� ���
		void DrawBackground(void);
		//���������� �������
		void DrawParticle(void);

		void OnObjectCollision(CContact *Contact);						// ���������� ��� ����������� ������������ ��������

		void ObjectAddToList(CObject *Obj);
		bool ObjectDeleteToList(CObject *Obj);

		void PEAddToList(CParticleEmitter *particleEmitter);
		bool PEDeleteToList(CParticleEmitter *particleEmitter);

		// �������� ������������
		void CollisionUpdate();
	};
};

#endif //_WORLD_H_