// object.cpp

#include <ctime>
#include "../world/world.h"
#include "object.h"

//----------------------------------------------------------------------------------------------------------

namespace PlatformEngine
{
	CObject::CObject()
	{
		inObject = false;
		color = {1, 1, 1, 1};
	}

	CObject::~CObject()
	{

	}

	///////////////////////////////////////////////////////////////////

	color4 CObject::GetColor()
	{
		return color;
	}

	void CObject::SetColor(color4 color)
	{
		this->color = color;
	}

	void CObject::Create(PlatformEngine::CWorld *World, float posX, float posY, float sizeX, float sizeY, CSprite * sprite)
	{
		this->posX = posX;
		this->posY = posY;
		this->sizeX = sizeX;
		this->sizeY = sizeY;
		this->sprite = sprite;
		this->world = World;
		this->rotate = 0.0f;
		this->objectTypeUpd = OBJECT_TYPE_STATIC;
	}

	///////////////////////////////////////////////////////////////////

	void CObject::GetPosition(float &x, float &y)
	{
		x = posX;
		y = posY;
	}

	void CObject::GetSize(float &x, float &y)
	{
		x = sizeX;
		y = sizeY;
	}

	float CObject::GetRotate()
	{
		return rotate;
	}

	int CObject::GetObjectType()
	{
		return objectTypeUpd;
	}

	void CObject::GetSpeed(float &x, float &y)
	{
		x = speedX;
		y = speedY;
	}

	///////////////////////////////////////////////////////////////////

	void CObject::SetPosition(float x, float y)
	{
		if(x != OBJECT_CURRENT_VALUE) posX = x;
		if(y != OBJECT_CURRENT_VALUE) posY = y;
	}

	void CObject::SetSize(float x, float y)
	{
		if(x != OBJECT_CURRENT_VALUE) sizeX = x;
		if(y != OBJECT_CURRENT_VALUE) sizeY = y;
	}

	void CObject::SetRotate(float angle)
	{
		rotate = angle;
	}

	void CObject::SetObjectType(int objtype)
	{
		objectTypeUpd = objtype;

		Stop();
	}


	void CObject::SetOnGround(bool val)
	{
		inGround = val;
	}

	void CObject::SetOnObject(bool val)
	{
		inObject = val;
	}
	///////////////////////////////////////////////////////////////////

	void CObject::Move(float speedX, float speedY)
	{
		if(speedX != OBJECT_CURRENT_VALUE) this->speedX = speedX;
		if(speedY != OBJECT_CURRENT_VALUE) this->speedY = speedY;
	}

	void CObject::SetAcceleration(float accX, float accY)
	{
		if(accX != OBJECT_CURRENT_VALUE) this->accX = accX;
		if(accY != OBJECT_CURRENT_VALUE) this->accY = accY;
	}

	void CObject::Stop()
	{
		this->accX = 0.0f;
		this->accY = 0.0f;
		this->speedX = 0.0f;
		this->speedY = 0.0f;
	}

	///////////////////////////////////////////////////////////////////

	void CObject::Update(float dTime)
	{
		if(!OnGround()) accY -= dTime*world->physics->GetGravity();

		speedX += dTime*accX;
		speedY += dTime*accY;

		posX += (dTime*speedX);
		posY += (dTime*speedY);

		// Если позиция Y ниже, чем земля, поставим объект на землю
		if(posY - (sizeX / 2) <= world->physics->GetGroundLevel())
		{
			posY = world->physics->GetGroundLevel()+sizeX/2;
			accY = 0.0f;
			speedY = 0.0f;
			inGround = true;
		}
		else
		{
			inGround = false;
		}

		//printf("cT %f, dT %f, pT %f, posX %f spX %f\n", cTime, dTime, pTime, posX, speedX);
	}

	bool CObject::OnGround()
	{
		return (inGround == true || inObject == true ? true : false);
	}
	///////////////////////////////////////////////////////////////////
};