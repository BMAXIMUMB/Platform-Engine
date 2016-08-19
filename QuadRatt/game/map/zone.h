// zone.h

#ifndef _ZONE_H_
#define _ZONE_H_

#include "../entity.h"

class IZone
{

protected:

	// Длина зоны, принимает случайное значение в заданном диапазоне
	// Диапазон может быть разным в каждом типе зоны
	int lenght;

	// Мир, в котором будут создаваться объекты
	PlatformEngine::CWorld *world;

public:

	IZone(PlatformEngine::CWorld *world);
	~IZone();

	// Функция создания объекта. Возвращает указатель на созданный объект
	CEntity* CreateObject(float &mapEnd);

	virtual void Generate(std::vector<CEntity*> &objectList, float &mapEnd) = 0;
};

class SimpleZone :public IZone
{
	// Тестовый вариант зоны


public:

	SimpleZone(PlatformEngine::CWorld *world);
	~SimpleZone();

	void Generate(std::vector<CEntity*> &objectList, float &mapEnd);
};

#endif // _ZONE_H_