// world.cpp

#include "world.h"
#include "layer.h"
#include "../application/application.h"

//----------------------------------------------------------------------------------------------------------

namespace PlatformEngine
{
	CWorld::CWorld(CApplication *app, WorldSettings Settings)
	{
		physics = new PlatformEngine::CPhysics;
		camera = new PlatformEngine::CCamera;
		background = new PlatformEngine::CLayer;

		this->collisionOn = Settings.collision;
		this->app = app;
		this->ObjectCollision = Settings.ObjectCollision;

		physics->SetGroundLevel(Settings.groundLevel);

		// Устанавливаем текущий мир преложению
		app->SetWorldID(this);
	}

	CWorld::~CWorld()
	{
		delete physics;
		delete camera;
	}

	CWorld* CWorld::GetID()
	{
		return this;
	}

	CApplication* CWorld::GetApp()
	{
		return app;
	}

	int CWorld::GetParticleCount()
	{
		int count = 0;
		//for(unsigned int i = 0; i < particleEmitterList.size(); i++) count += particleEmitterList[i]->GetParticleCount();
		for(auto i : particleEmitterList)
		{
			i->GetParticleCount();
		}

		return count;
	}

	void CWorld::ObjectAddToList(CObject *obj)
	{
		objectList.push_back(obj);
	}

	bool CWorld::ObjectDeleteToList(CObject *Obj)
	{
		for(auto it = objectList.begin(); it != objectList.end();it++)
		{
			if(*it == Obj)
			{
				objectList.erase(it);
				return true;
			}
		}
		return false;
	}

	void CWorld::PEAddToList(CParticleEmitter *particleEmitter)
	{
		particleEmitterList.push_back(particleEmitter);
	}

	bool CWorld::PEDeleteToList(CParticleEmitter *particleEmitter)
	{
		for(auto it = particleEmitterList.begin(); it != particleEmitterList.end(); it++)
		{
			if(*it == particleEmitter)
			{
				particleEmitterList.erase(it);
				return true;
			}
		}
		return false;
	}

	void CWorld::ObjectShow(CObject *Obj)
	{
		ObjectAddToList(Obj);
	}

	void CWorld::ObjectHide(CObject *Obj)
	{
		ObjectDeleteToList(Obj);
	}

	void CWorld::DestroyObject(CObject *Obj)
	{
		if(ObjectDeleteToList(Obj))
		{
			delete Obj;
		}
	}

	void CWorld::DestroyParticleEmitter(CParticleEmitter* PS)
	{
		if(PEDeleteToList(PS))
		{
			delete PS;
		}
	}

	CParticleEmitter* CWorld::CreateParticleEmitter(float pos_x, float pos_y, int count, int speed, ParticleEmitterSettings pes, PE::CSprite *Sprite)
	{
		CParticleEmitter *particleEmitter = new PE::CParticleEmitter;

		particleEmitter->Create(this, pos_x, pos_y, count, speed, pes, Sprite);
		PEAddToList(particleEmitter);

		return particleEmitter;
	}

	CQuad* CWorld::CreateObjectQuad(float posX, float posY, float sizeX, float sizeY, CSprite *sprite, int objtype)
	{
		CQuad *object = new PlatformEngine::CQuad();

		object->Create(this, posX, posY, sizeX, sizeY, sprite);
		object->SetObjectType(objtype);
		ObjectShow(object);

		return object;
	}

	void CWorld::Draw()
	{
		DrawBackground();										// Рисуем фон

		for(auto i: objectList)
		{
			float objinfo[5];
			color4 color;
			SpriteDrawSettings sds;

			i->GetPosition(objinfo[0], objinfo[1]);
			i->GetSize(objinfo[2], objinfo[3]);

			color = i->GetColor();

			objinfo[4] = i->GetRotate();

			sds.Cam = camera;
			sds.posX = objinfo[0];
			sds.posY = objinfo[1];
			sds.sizeX = objinfo[2];
			sds.sizeY = objinfo[3];
			sds.cmultiple[0] = color.r;
			sds.cmultiple[1] = color.g;
			sds.cmultiple[2] = color.b;
			sds.cmultiple[3] = color.a;

			i->sprite->Draw(app, sds);	// Рисуем каждый объект
		}
		
		// Рисуем партиклы
		DrawParticle();
	}

	void CWorld::DrawBackground()
	{
		background->Draw(app, camera);
	}

	void CWorld::DrawParticle()
	{
		for(auto i: particleEmitterList)
		{
			i->Draw();
		}
	}

	void CWorld::UpdateParticle(float dTime)
	{
		for(auto i : particleEmitterList)
		{
			i->Update(dTime);
		}
	}

	void CWorld::Update(float dTime)
	{
		for(auto i : objectList)
		{
			if(i->GetObjectType() == OBJECT_TYPE_DYNAMIC) i->Update(dTime);
		}

		if(collisionOn) CollisionUpdate();

		UpdateParticle(dTime);

		camera->Update(dTime);
	}

	void CWorld::CollisionUpdate()
	{
		// Проверка столкновений
		for(unsigned int i = 0; i < objectList.size(); i++)
		{
			float objpos[4], objsize[4];
			// Если объект динамический, чекнем его
			if(objectList[i]->GetObjectType() == OBJECT_TYPE_DYNAMIC)
			{
				objectList[i]->SetOnObject(false);
				// Узнаем позицию объекта и вычисляем граничные точки
				for(unsigned int k = 0; k < objectList.size(); k++)
				{
					// Если динамический объект != проверяемому
					if(objectList[i] != objectList[k])
					{
						// Узнаем позиции объектов
						objectList[i]->GetPosition(objpos[0], objpos[1]);
						objectList[i]->GetSize(objsize[0], objsize[1]);
						objectList[k]->GetPosition(objpos[2], objpos[3]);
						objectList[k]->GetSize(objsize[2], objsize[3]);

						// Проверяем, столкнулись ли объекты 
						double rcx = fabs(objpos[0] - objpos[2]);
						double rx = (objsize[0] / 2 + objsize[2] / 2);

						double rcy = fabs(objpos[1] - objpos[3]);
						double ry = (objsize[1] / 2 + objsize[3] / 2);

						if((rcx < rx) && (rcy < ry))
						{
							// Если да, создаем событие Contact и пеермещаем объект в нормальную позицию
							contactinfo ci;
							double overlap_x = rx - rcx;
							double overlap_y = ry - rcy;

							float x = 0, y = 0;
							if(overlap_x < overlap_y)
							{
								ci.rout_push = ROUT_PUSH_X;
								x = (float)overlap_x;

								if(objpos[0] < objpos[2])
								{
									x = -x;
								}
							}
							else
							{
								ci.rout_push = ROUT_PUSH_Y;
								objectList[i]->Move(OBJECT_CURRENT_VALUE, 0.0f);
								//ObjectList[i]->SetAcceleration(OBJECT_CURRENT_VALUE, 0.0f);
								y = (float)overlap_y;

								if(objpos[1] < objpos[3])
								{
									y = -y;
								}
								else
								{
									//printf("On ground %f\n", y);
									objectList[i]->SetOnObject(true);
								}
							}
							float opos[2];

							objectList[i]->GetPosition(opos[0], opos[1]);
							objectList[i]->SetPosition(opos[0] + x, opos[1] + y);

							//ObjectManager->DrawObject[i]->Move((x != 0 ? 0.0 : OBJECT_CURRENT_VALUE), (y != 0 ? 0.0 : OBJECT_CURRENT_VALUE));
							objectList[i]->SetAcceleration((x != 0 ? 0.0f : OBJECT_CURRENT_VALUE), (y != 0 ? 0.0f : OBJECT_CURRENT_VALUE));
							//printf("x %f, y %f, ry %f, rx %f\n", x, y, ry, rx);
							
							ci.object1 = objectList[i];
							ci.object2 = objectList[k];
							ci.overlap_x = x;
							ci.overlap_y = y;

							PlatformEngine::CContact Cont(ci);
							OnObjectCollision(&Cont);
						}
					}
				}
			}
		}
	}

	void CWorld::OnObjectCollision(CContact *Contact)
	{
		if(ObjectCollision != nullptr) ObjectCollision(Contact);
	}

	void CWorld::SetCollision(bool collision)
	{
		collisionOn = collision;
	}

	bool CWorld::GetCollision(void)
	{
		return collisionOn;
	}

	void CWorld::SetCollisionFunction(void(*CollisionObject) (CContact*))
	{
		this->ObjectCollision = CollisionObject;
	}
};