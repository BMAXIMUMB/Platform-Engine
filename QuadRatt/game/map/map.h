// map.h

#ifndef _MAP_H_
#define _MAP_H_

#include <vector>
#include "../entity.h"

#include "map_generator.h"

class CMap
{
private:

	// Хранилище всех физических объектов
	std::vector <CEntity*> objectList;

public:

	CMap();
	~CMap();

};

#endif //_MAP_H_