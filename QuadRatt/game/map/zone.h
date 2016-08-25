// zone.h

#ifndef _ZONE_H_
#define _ZONE_H_

#include "../entity.h"

struct MapInfo
{
	// Информация о карте

	/*
	*	Хранилище всех физических объектов
	*/
	std::vector<CEntity*> objectList;

	/*
	*	Конец сгенерированной карты
	*/
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

	/**
	*	Мир, в котором будут создаваться объекты
	*/
	PlatformEngine::CWorld *world = nullptr;

	//----------------------------------------------------------------------------------------------------------

	/**
	*	Ограничения и правила генерации для всех зон
	*/
	const float restMaxJumpHeight = 135.8f;

	/**
	*	Координата по Y первого объекта над землей
	*/
	const float restGroundLevel = 182.0f;

	/**
	*	Размер квадратного блока
	*/
	const float restBlockSize = 64.0f;

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

class TowerHole :public IZone
{
	// Тестовый вариант зоны


public:

	TowerHole(PlatformEngine::CWorld *world, int beginPos);
	~TowerHole();

	void Generate(std::vector<CEntity*> &objectList, float &mapEnd);

private:

	enum TowerType
	{
		Null,
		Type1,
		Type2,
		Type3
	};

	TowerType lastTowerType;

	/*
	*	Расстояние между башнями
	*/
	const float restTowerDistance = 448.0f;

	/*
	*	Дополнительный размер для отверстия в башне
	*/
	const float restMoreHoleSize = 10.0f;
};

#endif // _ZONE_H_