// zone.h

#ifndef _ZONE_H_
#define _ZONE_H_

#include "../entity.h"

struct MapInfo
{
	// Информация о карте

	// Хранилище всех физических объектов
	std::vector<CEntity*> objectList;

	// Конец сгенерированной карты
	float mapEnd;
};

//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------
class CMapGenerator;

class IZone
{

	friend CMapGenerator;

protected:

	/**
	*	Длина зоны, принимает случайное значение в заданном диапазоне
	*	Диапазон может быть разным в каждом типе зоны
	*/
	int lenght;

	/**
	*	Координата X начала зоны
	*/
	int beginPos;

	// Мир, в котором будут создаваться объекты
	PlatformEngine::CWorld *world;

public:

	/*
	*	world - мир, в котором будут создаваться объекты
	*	beginPos - позиция начала зоны по X
	*/
	IZone(PlatformEngine::CWorld *world, int beginPos);
	~IZone();

	/**
	*	Генерирует объекты по заданному алгоритму
	*/
	virtual void Generate(std::vector<CEntity*> &objectList, float &mapEnd) = 0;
};

class SimpleZone :public IZone
{
	// Тестовый вариант зоны


public:

	SimpleZone(PlatformEngine::CWorld *world, int beginPos);
	~SimpleZone();

	void Generate(std::vector<CEntity*> &objectList, float &mapEnd);
};

#endif // _ZONE_H_