// map.h

#ifndef _MAP_H_
#define _MAP_H_

#include <vector>

#include "map_generator.h"

class CMap
{
private:

	// Хранилище всех физических объектов
	std::vector <CEntity*> objectList;
	
	// Генератор карты
	CMapGenerator *mapGenerator;

	// Мир, в котором будут создаваться объекты
	PlatformEngine::CWorld *world;

public:

	CMap(PlatformEngine::CWorld *world);
	~CMap();
	
	// Удалить все объекты с карты
	void Clear(void);
};

#endif //_MAP_H_