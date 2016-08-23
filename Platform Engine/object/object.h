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
		float posX;						// Позиция объекта по X
		float posY;						// Позиция объекта по Y

		float sizeX;					// Размер по X(в пикселях)
		float sizeY;					// Размер по Y(в пикселях)

		float speedX;					// Скорость объекта по X
		float speedY;					// Скорость объекта по Y

		float accX;						// Ускорение объекта по X
		float accY;						// Ускорение объекта по Y
		
		float rotate;					// Угол поворота объекта
		
		CWorld *world;					// Мир, в котором создан объект

		bool inGround;					// На земле ли объект
		bool inObject;					// На объекте объект или нет
		CObject *inObjectID;			// Ид объекта, на котором объект

		color4 color;					// Object color

		// Остальная информация об объекте
		int objecttypeForm;
		int objecttypeUpd;

	public:
		CSprite *sprite;				// Спрайт объекта

		PLATFORMENGINE_API	CObject();
		PLATFORMENGINE_API	~CObject();

		PLATFORMENGINE_API	void Create(PlatformEngine::CWorld *World, float posX, float posY, float sizeX, float sizeY, CSprite * sprite);

		// Get...
		PLATFORMENGINE_API	void GetPosition(float &x, float &y);						// Узнать позицию объекта
		PLATFORMENGINE_API	void GetSize(float &x, float &y);							// Узнать размеры объекта
		PLATFORMENGINE_API	void GetSpeed(float &x, float &y);
		PLATFORMENGINE_API	int GetObjectType(void);
		PLATFORMENGINE_API	float GetRotate(void);										// Узнать угол поворота объекта
		PLATFORMENGINE_API	color4 GetColor(void);

		// Set...
		PLATFORMENGINE_API	void SetPosition(float x, float y);							// Изменить позицию объекта
		PLATFORMENGINE_API	void SetSize(float x, float y);								// Изменить размер объекта
		PLATFORMENGINE_API	void SetRotate(float angle);								// Изменить угол поворота объекта
		PLATFORMENGINE_API	void SetObjectType(int objtype);							// Изменить тип объекта
		PLATFORMENGINE_API  void SetOnGround(bool val);
		PLATFORMENGINE_API  void SetOnObject(bool val);
		PLATFORMENGINE_API	void SetColor(color4 color);

		PLATFORMENGINE_API	void Move(float speedX, float speedY);						// Двигать объект
		PLATFORMENGINE_API	void Stop(void);											// Остановить объект
		PLATFORMENGINE_API	void SetAcceleration(float accX, float accY);				// Задать ускорение

		PLATFORMENGINE_API	void Update(float dTime);

		PLATFORMENGINE_API	bool OnGround();
		//PLATFORMENGINE_API	virtual void Draw(void) = 0;							// Отрисовать объект
	};
};

#endif //_OBJECT_H_