// map.h

#ifndef _MAP_H_
#define _MAP_H_

#include <vector>

#include "map_generator.h"

class CMap
{
private:
	 
	// Хранилище всех физических объектов
	std::vector <IEntity*> objectList;
	
	// Генератор карты
	CMapGenerator *mapGenerator;

	// Мир, в котором будут создаваться объекты
	PlatformEngine::CWorld *world;

	/**
	*	Конец сгенерированной карты
	*/
	float mapEnd;

public:

	CMap(PlatformEngine::CWorld *world);
	~CMap();
	
	// Удалить все объекты с карты
	void Clear(void);

	// Функция проверки объектов
	void Check(void);

	// Изменить стартовую позицию генерации карты
	void SetGeneratePos(float position);

	/**
	*	Получить позицию X конца карты
	*/
	float GetMapEnd(void);

	/**
	*	Изменить позицию X конца карты
	*/
	void SetMapEnd(float value)
	{
		mapEnd = value;
	}


	/**
	*	Фабричные методы создания объектов
	*/

	CBlock* CreateBlock(float posX, float posY);
	CMiniPlatform* CreateMiniPlatform(float posX, float posY);
};

#endif //_MAP_H_