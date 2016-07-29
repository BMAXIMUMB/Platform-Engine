// map_generator.h

#ifndef _MAP_GENERATOR_H_
#define _MAP_GENERATOR_H_

#include <vector>
#include "../entity.h"

class CMapGenerator
{
private:

	// Мир, в котором будут создаваться объекты
	PlatformEngine::CWorld *world;

	// Функция создания объекта. Возвращает указатель на созданный объект
	CEntity* CreateObject(void);

public:
	
	// Конструктор. world - указатель на объект мира
	CMapGenerator(PlatformEngine::CWorld *world);

	// Деструктор. Нихуя не делает
	~CMapGenerator();

	// Функция генерации объектов. В качестве аргумента принимает
	// указатель на список объектов, куда положить сгенерированные объекты
	void Generate(std::vector<CEntity*> objectList);
};

#endif //_MAP_GENERATOR_H_
