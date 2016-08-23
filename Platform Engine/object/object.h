// object.h

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "../graphics/sprite/sprite.h"
#include "../graphics/color/color.h"
#include "particles.h"

//----------------------------------------------------------------------------------------------------------

// OBJECT_TYPES
#define OBJECT_TYPE_QUAD					(0x1)
#define OBJECT_TYPE_TRIANGLE				(0x2)
#define OBJECT_TYPE_CIRCLE					(0x3)

#define OBJECT_TYPE_STATIC					(0x4)
#define OBJECT_TYPE_DYNAMIC					(0x5)

#define OBJECT_CURRENT_VALUE				(0xffff)

namespace PlatformEngine
{
	class CWorld;

	class CObject
	{
	protected:
		float posX;						// ������� ������� �� X
		float posY;						// ������� ������� �� Y

		float sizeX;					// ������ �� X(� ��������)
		float sizeY;					// ������ �� Y(� ��������)

		float speedX;					// �������� ������� �� X
		float speedY;					// �������� ������� �� Y

		float accX;						// ��������� ������� �� X
		float accY;						// ��������� ������� �� Y
		
		float rotate;					// ���� �������� �������
		
		CWorld *world;					// ���, � ������� ������ ������

		bool inGround;					// �� ����� �� ������
		bool inObject;					// �� ������� ������ ��� ���
		CObject *inObjectID;			// �� �������, �� ������� ������

		color4 color;					// Object color

		// ��������� ���������� �� �������
		int objecttypeForm;
		int objecttypeUpd;

	public:
		CSprite *sprite;				// ������ �������

		PLATFORMENGINE_API	CObject();
		PLATFORMENGINE_API	~CObject();

		PLATFORMENGINE_API	void Create(PlatformEngine::CWorld *World, float posX, float posY, float sizeX, float sizeY, CSprite * sprite);

		// Get...
		PLATFORMENGINE_API	void GetPosition(float &x, float &y);						// ������ ������� �������
		PLATFORMENGINE_API	void GetSize(float &x, float &y);							// ������ ������� �������
		PLATFORMENGINE_API	void GetSpeed(float &x, float &y);
		PLATFORMENGINE_API	int GetObjectType(void);
		PLATFORMENGINE_API	float GetRotate(void);										// ������ ���� �������� �������
		PLATFORMENGINE_API	color4 GetColor(void);

		// Set...
		PLATFORMENGINE_API	void SetPosition(float x, float y);							// �������� ������� �������
		PLATFORMENGINE_API	void SetSize(float x, float y);								// �������� ������ �������
		PLATFORMENGINE_API	void SetRotate(float angle);								// �������� ���� �������� �������
		PLATFORMENGINE_API	void SetObjectType(int objtype);							// �������� ��� �������
		PLATFORMENGINE_API  void SetOnGround(bool val);
		PLATFORMENGINE_API  void SetOnObject(bool val);
		PLATFORMENGINE_API	void SetColor(color4 color);

		PLATFORMENGINE_API	void Move(float speedX, float speedY);						// ������� ������
		PLATFORMENGINE_API	void Stop(void);											// ���������� ������
		PLATFORMENGINE_API	void SetAcceleration(float accX, float accY);				// ������ ���������

		PLATFORMENGINE_API	void Update(float dTime);

		PLATFORMENGINE_API	bool OnGround();
		//PLATFORMENGINE_API	virtual void Draw(void) = 0;							// ���������� ������
	};
};

#endif //_OBJECT_H_