// zone.h

#ifndef _ZONE_H_
#define _ZONE_H_

#include "../entity.h"

class CMap;

struct MapInfo
{
	// Информация о карте

	/**
	*	Хранилище всех физических объектов
	*/
	std::vector<IEntity*> objectList;

	/**
	*	Конец сгенерированной карты
	*/
	float mapEnd;
};


struct ZoneInfo
{
	CMap* map;

	int beginPos;

	int lastZoneID;
};
//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------
class CMapGenerator;

class IZone
{

	friend CMapGenerator;

protected:

	CMap* map;

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

	/**
	*	ID предыдущей зоны
	*/
	int prevZoneID;

	/**
	*	Создан ли хоть один объект
	*/
	bool isCreated;

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

	/**
	*	Ширина мини-платформы
	*/
	const float restMiniPlatformSize = 64.0f;

public:

	/**
	*	world - мир, в котором будут создаваться объекты
	*	beginPos - позиция начала зоны по X
	*/
	IZone(ZoneInfo zi);
	~IZone();

	/**
	*	Генерирует объекты по заданному алгоритму
	*/
	virtual void Generate() = 0;
};

class TowerHole :public IZone
{

public:

	TowerHole(ZoneInfo zi);
	~TowerHole();

	void Generate();

private:

	enum class TowerType
	{
		Null,
		Type1,
		Type2,
		Type3
	};

	TowerType lastTowerType;

	/**
	*	Расстояние между башнями
	*/
	const float restTowerDistance = 448.0f;

	/**
	*	Дополнительный размер для отверстия в башне
	*/
	const float restMoreHoleSize = 10.0f;
};

class TowerStairs :public IZone
{

public:
	TowerStairs(ZoneInfo zi);
	~TowerStairs();

	void Generate();

private:
	
	/**
	*	Высота пролета последней башни
	*/
	int lastHoleLevel;

	//----------------------------------------------------------------------------------------------------------

	/**
	*	Расстояние между башнями
	*/
	const float restTowerDistance = 192.0f;

	/**
	*	Расстояние между самой первой башней и предыдущей зоной
	*/
	const float restZoneDistance = 640;

	/**
	*	Размер пролета в блоках
	*/
	const float restHoleSize = 3;

	/**
	*	Высота башни
	*/
	const int restTowerHeight = 8;

	//----------------------------------------------------------------------------------------------------------

	/**
	*	Создать башню
	*/
	void TowerCreate(int holeLevel);
};

class PlatformStairs :public IZone
{

public:
	PlatformStairs(ZoneInfo zi);
	~PlatformStairs();

	void Generate();

private:

	/**
	*	Уровень предыдущей ступени
	*/
	int lastLevel;

	/**
	*	Направление последней ступени
	*	Используется для избежания повторений и длинных лестниц в одну сторону
	*/
	int lastDirection;
	
	/**
	*	Счетчик ступеней с ненулевым направлением
	*	Если генерируется ступень с направлением "0", счетчик сбрасывается
	*/
	int directionCounter;

	//----------------------------------------------------------------------------------------------------------

	/**
	*	Расстояние между ступенями (в блоках)
	*/
	const int restStageDistance = 4;

	/**
	*	Начальная высота ( высота первой ступеньки )
	*/
	const float restStartPosY = 202.0f;

	//----------------------------------------------------------------------------------------------------------
};

#endif // _ZONE_H_