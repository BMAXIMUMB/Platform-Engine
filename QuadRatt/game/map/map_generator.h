// map_generator.h

#ifndef _MAP_GENERATOR_H_
#define _MAP_GENERATOR_H_

#include <vector>

#include "zone.h"

class CMapGenerator
{
	/*
		Генерирует объекты на карте с помощью специальных алгоритмов и правил

	
	*/

private:

	// Мир, в котором будут создаваться объекты
	PlatformEngine::CWorld *world;

	// Функция создания объекта. Возвращает указатель на созданный объект
	CEntity* CreateObject(float &mapEnd);

public:
	
	// Конструктор. world - указатель на объект мира
	CMapGenerator(PlatformEngine::CWorld *world);

	// Деструктор. Нихуя не делает ( пока ) 
	~CMapGenerator();

	// Функция генерации объектов. В качестве аргумента принимает
	// указатель на список объектов, куда нужно положить сгенерированные объекты
	void Generate(std::vector<CEntity*> &objectList, float &mapEnd);
};

#endif //_MAP_GENERATOR_H_
