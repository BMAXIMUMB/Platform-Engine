// particles.h

#ifndef _PARTICLES_H_
#define _PARTICLES_H_

#include "../graphics/sprite/sprite.h"
#include <vector>

#define E_DESTROY_WAIT				(0x1)
#define E_DEFAULT_INTERVAL			(0.010)		//sec

struct pvec2
{
	float a, b;
};

struct color4
{
	float r, g, b, a;
	color4 operator *(float value)
	{
		color4 c;
		c.r = r*value;
		c.g = g*value;
		c.b = b*value;
		c.a = a*value;
		return c;
	}

	color4 operator +=(color4 c)
	{
		r += c.r;
		g += c.g;
		b += c.b;
		a += c.a;

		return *this;
	}
};

struct ParticleSettings
{
	float posX,
	posY,
	velocityX,
	velocityY,
	angle,
	velocityAngle,
	size,
	velocitySize;
	color4 color,
	velocityColor;
	PE::CSprite *sprite;
	float time;
};

struct ParticleDrawInfo
{
	float posX,
	posY,
	sizeX,
	sizeY,
	angle;
	color4 color;
};

struct ParticleEmitterSettings
{
	float posxRnd,
	posyRnd,
	size,
	sizeRnd,
	angleRnd;
	color4 color;

	pvec2 velX;
	pvec2 velY;
	pvec2 velXRnd;
	pvec2 velYRnd;
	color4 velColor;
	float velSizeRnd,
	velAngle,
	velAngleRnd;

	float time;
};

namespace PlatformEngine
{
	class CWorld;

	// Класс частицы
	class CParticle
	{
	private:
		// Основные параметры
		float posX;
		float posY;
		float angle;
		float size;
		float velocityAngle;
		float velocitySize;
		float velocityX;
		float velocityY;

		color4 velocityColor;
		color4 color;

		// Время существования частицы
		float time;

	public:

		CParticle(ParticleSettings ps);

		bool Disappear(void);

		void Update(float dTime);

		//Применение новых параметров
		void Reset(ParticleSettings ps);

		ParticleDrawInfo GetDrawInfo(void);
	};

	class CParticleEmitter
	{
	private:

		std::vector<CParticle*> particleList;

		ParticleEmitterSettings pes;

		CSprite *sprite;
		CWorld *world;
		
		// Инфа об объекте, к которому прикреплен объект
		CObject *attachedObject;
		// Смещение относительно объекта
		float offsetX, offsetY;

		// Остальная информация
		float posX;
		float posY;
		float timeInterval;
		int speed;
		int count;
		int createdCount;

	public:
		CParticleEmitter();
		~CParticleEmitter();

		void ParticleAddToList(PE::CParticle *p);
		bool ParticleDeleteToList(PE::CParticle *p);
		bool ParticleDeleteToList(int index);
		void Release(void);

		CParticle* ParticleCreate(ParticleSettings ps);

		void ParticleDestroy(PE::CParticle *p);
		void ParticleDestroy(int index);
		void ParticleDraw(int index);
		
		int GetParticleCount(void);

		PLATFORMENGINE_API void AttachToObject(CObject *Object, float offsetx = 0.0, float offsety = 0.0);

		void Create(PE::CWorld *World, float pos_x, float pos_y, int count, int speed, ParticleEmitterSettings pes, PE::CSprite *Sprite);
		
		void Update(float dt);
		void Draw(void);
	};
};

#endif //_PARTICLES_H_