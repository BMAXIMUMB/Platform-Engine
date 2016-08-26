// map_generator.h

#ifndef _MAP_GENERATOR_H_
#define _MAP_GENERATOR_H_

#include <vector>

#include "zone.h"

class CMapGenerator
{
	/**
	*	Генерирует объекты на карте с помощью специальных алгоритмов и правил
	*
	*
	*/

private:

	// Мир, в котором будут создаваться объекты
	PlatformEngine::CWorld *world;

	// Текущая зона
	IZone * currentZone = nullptr;

public:
	
	// Конструктор. world - указатель на объект мира
	CMapGenerator(PlatformEngine::CWorld *world);

	// Деструктор. Нихуя не делает ( пока ) 
	~CMapGenerator();

	void Reset(void);

	/**
	*	Функция генерации объектов. В качестве аргумента принимает
	*	указатель на список объектов, куда нужно положить сгенерированные объекты
	*/
	void Generate(std::vector<CEntity*> &objectList, float &mapEnd);

	/**
	*	Создает новую зону
	*	beginPos - позиция начала зоны по X
	*/
	IZone* CreateZone(float beginPos);
};

#endif //_MAP_GENERATOR_H_
