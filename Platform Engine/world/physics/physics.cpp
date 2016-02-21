// physics.cpp

#include "physics.h"

namespace PlatformEngine
{
	CPhysics::CPhysics()
	{
		gravity = GRAVITY_DEFAULT;
		groundLevel = GROUND_LEVEL_DEFAULT;
	}

	CPhysics::~CPhysics()
	{
		
	}

	///////////////////////////////////////////////////////////////////
	
	float CPhysics::GetGroundLevel()
	{
		return groundLevel;
	}

	float CPhysics::GetGravity()
	{
		return gravity;
	}

	///////////////////////////////////////////////////////////////////

	void CPhysics::SetGroundLevel(float gLevel)
	{
		groundLevel = gLevel;
	}

	void CPhysics::SetGravity(float gravity)
	{
		CPhysics::gravity = gravity;
	}
};