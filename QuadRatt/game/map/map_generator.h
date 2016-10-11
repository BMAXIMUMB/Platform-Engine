// map_generator.h

#ifndef _MAP_GENERATOR_H_
#define _MAP_GENERATOR_H_

#include <vector>

#include "zone.h"

class CMap;

class CMapGenerator
{
	/**
	*	Генерирует объекты на карте с помощью специальных алгоритмов и правил
	*
	*
	*/

private:

	/**
	*	Карта, к которой относится генератор
	*/
	CMap* map;

	/**
	*	Текущая зона
	*/
	IZone * currentZone = nullptr;

	/**
	*	Номер последней сгенерированной зоны
	*/
	int lastZoneID	= NULL;

public:
	
	/**
	*	Конструктор. map - указатель на карту
	*/
	CMapGenerator(CMap *map);

	/**
	*	Деструктор. Нихуя не делает ( пока ) 
	*/
	~CMapGenerator();

	/**
	*	Сброс зон
	*/
	void Reset(void);

	/**
	*	Функция генерации объектов. В качестве аргумента принимает
	*	указатель на список объектов, куда нужно положить сгенерированные объекты
	*/
	void Generate(/*std::vector<IEntity*> &objectList, float &mapEnd*/);

	/**
	*	Создает новую зону
	*/
	IZone* CreateZone();
};

#endif //_MAP_GENERATOR_H_
