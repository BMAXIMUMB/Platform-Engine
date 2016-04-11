// camera.h

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../../platform_engine.h"

//----------------------------------------------------------------------------------------------------------

namespace PlatformEngine
{
	class CObject;

	class CCamera
	{
	private:
		CObject *attachedObject;					// Объект, за которым следит камера

	public:
		float posX;									// Позиция X камеры
		float posY;									// Позиция Y камеры
		float offsetX;
		float offsetY;
		float speedX;
		float speedY;
		float fixedPosX;
		float fixedPosY;

		bool move;

		PLATFORMENGINE_API	CCamera();

		PLATFORMENGINE_API	void SetPosition(float x, float y);
		PLATFORMENGINE_API	void SetSpeed(float x, float y);

		PLATFORMENGINE_API	void GetPosition(float &x, float &y);
		PLATFORMENGINE_API	void GetSpeed(float &x, float &y);
		PLATFORMENGINE_API	CObject* GetAttachedObject(void);

		PLATFORMENGINE_API	void AttachToObject(CObject *Obj, float offset_x = 0.0f, float offset_y = 0.0f, float fixed_pos_x = 0.0f, float fixed_pos_y = 0.0f);
		PLATFORMENGINE_API	void Update(float dTime);
	};
};

#endif //_CAMERA_H_