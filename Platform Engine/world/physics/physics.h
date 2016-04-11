// physics.h

#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "../../platform_engine.h"

//----------------------------------------------------------------------------------------------------------

// DEFAULT VALUES
#define GRAVITY_DEFAULT					(9800.0)						// �������� ���������� �� ���������
#define GROUND_LEVEL_DEFAULT			(0.0)							// �������� ����� �� ���������

namespace PlatformEngine
{
	class CPhysics
	{
	private:
		float groundLevel;												// ������� �����
		float gravity;													// ���� ����������

	public:
		PLATFORMENGINE_API	CPhysics();
		PLATFORMENGINE_API	~CPhysics();

		PLATFORMENGINE_API	float GetGroundLevel(void);					// ������ ������� �����
		PLATFORMENGINE_API	float GetGravity(void);						// ������ �������� ����������

		PLATFORMENGINE_API	void SetGroundLevel(float gLevel);			// �������� ������� �����
		PLATFORMENGINE_API	void SetGravity(float gravity);
	};
};

#endif //_PHYSICS_H_