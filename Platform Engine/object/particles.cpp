// particles.cpp

#include "../world/world.h"
#include "../application/application.h"
#include "particles.h"

//----------------------------------------------------------------------------------------------------------

#define ATVC(p1, p2) cos(p1) * p2
#define ATVS(p1, p2) sin(p1) * p2

namespace PlatformEngine
{
	CParticle::CParticle(ParticleSettings ps)
	{
		this->posX = ps.posX;
		this->posY = ps.posY;
		this->size = ps.size;
		this->angle = ps.angle;
		this->velocityX = ps.velocityX;
		this->velocityY = ps.velocityY;
		this->velocitySize = ps.velocitySize;
		this->velocityAngle = ps.velocityAngle;
		this->velocityColor = ps.velocityColor;
		this->color = ps.color;
		this->time = ps.time;
	}

	bool CParticle::Disappear()
	{
		return (time <= 0 || size <= 0) ? true : false;
	}

	void CParticle::Reset(ParticleSettings ps)
	{
		this->posX = ps.posX;
		this->posY = ps.posY;
		this->size = ps.size;
		this->angle = ps.angle;
		this->velocityX = ps.velocityX;
		this->velocityY = ps.velocityY;
		this->velocitySize = ps.velocitySize;
		this->velocityAngle = ps.velocityAngle;
		this->velocityColor = ps.velocityColor;
		this->color = ps.color;
		this->time = ps.time;
		
	}

	void CParticle::Update(float dTime)
	{
		time -= dTime;

		posX += velocityX*dTime;
		posY += velocityY*dTime;

		angle += velocityAngle*dTime;
		size += velocitySize*dTime;
		
		color += (velocityColor * dTime);
	}

	ParticleDrawInfo CParticle::GetDrawInfo()
	{
		ParticleDrawInfo pdi;

		pdi.posX = this->posX;
		pdi.posY = this->posY;
		pdi.sizeX = this->size;
		pdi.sizeY = this->size;
		pdi.angle = this->angle;
		pdi.color = this->color;

		return pdi;
	}

	///////////////////////////////////////////////////////////////////

	CParticleEmitter::CParticleEmitter()
	{
		count = 0;
		createdCount = 0;
		timeInterval = 0;
		
		randomDevice = new CRandomDevice;
		attachedObject = nullptr;
	}

	CParticleEmitter::~CParticleEmitter()
	{
		Release();
		delete randomDevice;
	}

	void CParticleEmitter::AttachToObject(CObject *Object, float offsetx, float offsety)
	{
		attachedObject = Object;

		this->offsetX = offsetx;
		this->offsetY = offsety;
	}
	
	void CParticleEmitter::Release()
	{
		// Удаляем все частицы
		for(unsigned int i = 0; i < particleList.size(); i++)
		{
			delete particleList[i];
		}
	}

	void CParticleEmitter::ParticleAddToList(PE::CParticle *p)
	{
		particleList.push_back(p);
	}

	bool CParticleEmitter::ParticleDeleteToList(PE::CParticle *p)
	{
		for(auto it = particleList.begin(); it != particleList.end(); it++)
		{
			if(*it == p)
			{
				particleList.erase(it);
				return true;
			}
		}
		return false;
	}

	bool CParticleEmitter::ParticleDeleteToList(int index)
	{
		auto it = particleList.begin();
		particleList.erase(it + index);
		return true;
	}

	CParticle*  CParticleEmitter::ParticleCreate(ParticleSettings ps)
	{
		CParticle* p = new CParticle(ps);

		ParticleAddToList(p);
		createdCount++;

		return p;
	}
	
	void CParticleEmitter::ParticleDestroy(PE::CParticle *p)
	{
		if(ParticleDeleteToList(p))
		{
			createdCount--;
			delete p;
		}
	}

	void CParticleEmitter::ParticleDestroy(int index)
	{
		delete particleList[index];
		ParticleDeleteToList(index);
		createdCount--;
	}

	int CParticleEmitter::GetParticleCount()
	{
		return createdCount;
	}

	void CParticleEmitter::Create(PE::CWorld *World, float pos_x, float pos_y, int count, int speed, ParticleEmitterSettings pes, PE::CSprite *Sprite)
	{
		this->world = World;
		this->posX = pos_x;
		this->posY = pos_y;
		this->count = count;
		this->sprite = Sprite;
		this->pes = pes;
		this->createdCount = 0;
		this->speed = speed;

		// Преобразование градусов в радианы
		#pragma warning(disable:4244)
		this->pes.velX.a = this->pes.velX.a * M_PI / 180;
		this->pes.velY.a = this->pes.velY.a * M_PI / 180;
		this->pes.velXRnd.a = this->pes.velXRnd.a * M_PI / 180;
		this->pes.velYRnd.a = this->pes.velYRnd.a * M_PI / 180;
		#pragma warning(default:4244)
	}

	void CParticleEmitter::Update(float dt)
	{
		timeInterval += dt;

		if(attachedObject != nullptr)
		{
			float tpos[2];
			(attachedObject->GetPosition(tpos[0], tpos[1]));
			posX = tpos[0] + offsetX;
			posY = tpos[1] + offsetY;
		}

		for(unsigned int i = 0; i < particleList.size(); i++)
		{
			if(!particleList[i]->Disappear())
			{
				particleList[i]->Update(dt);
			}
			else
			{
				ParticleSettings ps;
				
				ps.posX = this->posX + randomDevice->GetRealValue<float>(-pes.posxRnd, pes.posxRnd);
				ps.posY = this->posY + randomDevice->GetRealValue<float>(-pes.posyRnd, pes.posyRnd);
				ps.size = pes.size + randomDevice->GetRealValue<float>(-pes.sizeRnd, pes.sizeRnd);
				ps.angle = randomDevice->GetRealValue<float>(-pes.angleRnd, pes.angleRnd);
				ps.color = pes.color;
				ps.time = pes.time;

				ps.velocityX = ATVC(pes.velX.a + pes.velX.a*randomDevice->GetRealValue<float>(-pes.velXRnd.a, pes.velXRnd.a), pes.velX.b + pes.velX.b*randomDevice->GetRealValue<float>(-pes.velXRnd.b, pes.velXRnd.b));
				ps.velocityY = ATVS(pes.velY.a + pes.velY.a*randomDevice->GetRealValue<float>(-pes.velYRnd.a, pes.velYRnd.a), pes.velY.b + pes.velX.b*randomDevice->GetRealValue<float>(-pes.velYRnd.b, pes.velYRnd.b));
				ps.velocityColor = pes.velColor;
				ps.velocitySize = pes.velSizeRnd;
				ps.velocityAngle = pes.velAngle + randomDevice->GetRealValue<float>(-pes.velAngleRnd, pes.velAngleRnd);

				particleList[i]->Reset(ps);
			}
		}
		if(createdCount < count)
		{
			if(timeInterval >= E_DEFAULT_INTERVAL)
			{
				// Расчитываем, сколько частиц нужно создать
				for(int i = 0; i < speed*timeInterval; i++)
				{
					if(createdCount >= count) break;

					ParticleSettings ps;

					ps.posX = this->posX + randomDevice->GetRealValue<float>(-pes.posxRnd, pes.posxRnd);
					ps.posY = this->posY + randomDevice->GetRealValue<float>(-pes.posyRnd, pes.posyRnd);
					ps.size = pes.size + randomDevice->GetRealValue<float>(-pes.sizeRnd, pes.sizeRnd);
					ps.angle = randomDevice->GetRealValue<float>(-pes.angleRnd, pes.angleRnd);
					ps.color = pes.color;
					ps.time = pes.time;

					ps.velocityX = ATVC(pes.velX.a + pes.velX.a*randomDevice->GetRealValue<float>(-pes.velXRnd.a, pes.velXRnd.a), pes.velX.b + pes.velX.b*randomDevice->GetRealValue<float>(-pes.velXRnd.b, pes.velXRnd.b));
					ps.velocityY = ATVS(pes.velY.a + pes.velY.a*randomDevice->GetRealValue<float>(-pes.velYRnd.a, pes.velYRnd.a), pes.velY.b + pes.velX.b*randomDevice->GetRealValue<float>(-pes.velYRnd.b, pes.velYRnd.b));
					ps.velocityColor = pes.velColor;
					ps.velocitySize = pes.velSizeRnd;
					ps.velocityAngle = pes.velAngle + randomDevice->GetRealValue<float>(-pes.velAngleRnd, pes.velAngleRnd);

					ParticleCreate(ps);
				}

				timeInterval = 0;
			}
			
		}
	}

	void CParticleEmitter::ParticleDraw(int index)
	{
		ParticleDrawInfo pdi = particleList[index]->GetDrawInfo();
		SpriteDrawSettings sds;

		sds.posX = pdi.posX;
		sds.posY = pdi.posY;
		sds.sizeX = pdi.sizeX;
		sds.sizeY = pdi.sizeY;
		sds.rot = pdi.angle;
		sds.cmultiple[0] = pdi.color.r;
		sds.cmultiple[1] = pdi.color.g;
		sds.cmultiple[2] = pdi.color.b;
		sds.cmultiple[3] = pdi.color.a;
		sds.Cam = world->camera;

		sprite->Draw(world->GetApp(), sds);
	}

	void CParticleEmitter::Draw()
	{
		if(!particleList.empty())
		{
			for(unsigned int i = 0; i < particleList.size(); i++)
			{
				ParticleDraw(i);
			}
		}
	}
};