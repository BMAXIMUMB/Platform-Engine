// camera.cpp

#include "camera.h"
#include "../../object/object.h"

namespace PlatformEngine
{
	CCamera::CCamera()
	{
		posX = 0.0;
		posY = 0.0;
		offsetX = 0.0;
		offsetY = 0.0;
		speedX = 0.0;
		speedY = 0.0;
		fixedPosX = 0.0;
		fixedPosY = 0.0;
		move = false;

		attachedObject = nullptr;
	}

	void CCamera::Reset()
	{
		posX = 0.0;
		posY = 0.0;
		offsetX = 0.0;
		offsetY = 0.0;
		speedX = 0.0;
		speedY = 0.0;
		fixedPosX = 0.0;
		fixedPosY = 0.0;
		move = false;

		attachedObject = nullptr;
	}

	void CCamera::SetPosition(float x, float y)
	{
		posX = x;
		posY = y;
	}
	
	void CCamera::SetSpeed(float x, float y)
	{
		speedX = x;
		speedY = y;

		move = true;
	}

	void CCamera::GetPosition(float &x, float &y)
	{
		x = posX;
		y = posY;
	}

	void CCamera::GetSpeed(float &x, float &y)
	{
		x = speedX;
		y = speedY;
	}

	void CCamera::AttachToObject(CObject *Obj, float offset_x, float offset_y, float fixed_pos_x, float fixed_pos_y)
	{
		move = false;

		this->attachedObject = Obj;
		this->offsetX = offset_x;
		this->offsetY = offset_y;
		this->fixedPosX = fixed_pos_x;
		this->fixedPosY = fixed_pos_y;

		Obj->GetSpeed(speedX, speedY);
		Obj->GetPosition(posX, posY);
	}

	void CCamera::DeAttachToObject()
	{
		attachedObject = nullptr;
	}

	void CCamera::Update()
	{
		if(attachedObject != nullptr)
		{
			float opos[2];
			attachedObject->GetPosition(opos[0], opos[1]);

			if(fixedPosX == 0.0) posX = opos[0];
			else posX = fixedPosX;

			if(fixedPosY == 0.0) posY = opos[1];
			else posY = fixedPosY;
		}
	}

	void CCamera::Update(float dTime)
	{
		if(attachedObject != nullptr)
		{
			float opos[2];
			attachedObject->GetPosition(opos[0], opos[1]);

			if(fixedPosX == 0.0) posX = opos[0];
			else posX = fixedPosX;

			if(fixedPosY == 0.0) posY = opos[1];
			else posY = fixedPosY;
		}
		else if(move)
		{
			posX += speedX*dTime;
			posY += speedY*dTime;
		}
	}

	CObject* CCamera::GetAttachedObject()
	{
		return attachedObject;
	}
};