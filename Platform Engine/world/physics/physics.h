// physics.h

#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "../../platform_engine.h"

//----------------------------------------------------------------------------------------------------------

// DEFAULT VALUES
#define GRAVITY_DEFAULT					(9800.0)						// Значение гравитации по умолчанию
#define GROUND_LEVEL_DEFAULT			(0.0)							// Значение земли по умолчанию

namespace PlatformEngine
{
	class CPhysics
	{
	private:
		float groundLevel;												// Уровень земли
		float gravity;													// Сила притяжения

	public:
		PLATFORMENGINE_API	CPhysics();
		PLATFORMENGINE_API	~CPhysics();

		PLATFORMENGINE_API	float GetGroundLevel(void);					// Узнать уровень земли
		PLATFORMENGINE_API	float GetGravity(void);						// Узнать значение гравитации

		PLATFORMENGINE_API	void SetGroundLevel(float gLevel);			// Изменить уровень земли
		PLATFORMENGINE_API	void SetGravity(float gravity);
	};
};

#endif //_PHYSICS_H_