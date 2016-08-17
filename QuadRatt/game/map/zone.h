// zone.h

#ifndef _ZONE_H_
#define _ZONE_H_

#include "../entity.h"

class IZone
{

private:

	// ƒлина зоны, принимает случайное значение в заданном диапазоне
	// ƒиапазон может быть разным в каждом типе зоны
	int lenght;

public:

	IZone();
	~IZone();
};

class SimpleZone :public IZone
{
	// “естовый вариант зоны


public:

	SimpleZone();
	~SimpleZone();
};

#endif // _ZONE_H_