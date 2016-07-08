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
		CObject *attachedObject;					// ������, �� ������� ������ ������

	public:
		float posX;									// ������� X ������
		float posY;									// ������� Y ������
		float offsetX;
		float offsetY;
		float speedX;
		float speedY;
		float fixedPosX;
		float fixedPosY;

		float oldPosX;
		float oldPosY;

		bool move;

		PLATFORMENGINE_API	CCamera();

		PLATFORMENGINE_API  void Reset(void);

		PLATFORMENGINE_API	void SetPosition(float x, float y);
		PLATFORMENGINE_API	void SetSpeed(float x, float y);

		PLATFORMENGINE_API	void GetPosition(float &x, float &y);
		PLATFORMENGINE_API	void GetSpeed(float &x, float &y);
		PLATFORMENGINE_API	CObject* GetAttachedObject(void);

		PLATFORMENGINE_API	void AttachToObject(CObject *Obj, float offset_x = 0.0f, float offset_y = 0.0f, float fixed_pos_x = 0.0f, float fixed_pos_y = 0.0f);
		PLATFORMENGINE_API  void DeAttachToObject(void);
		PLATFORMENGINE_API	void Update(float dTime);
		PLATFORMENGINE_API	void Update(void);
	};
};

#endif //_CAMERA_H_