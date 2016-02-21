// world.h

#ifndef _GWORLD_H_
#define _GWORLD_H_

#include "../main.h"
#include "entity.h"
#include "background.h"

class gWorld
{
	friend class Game;
private:
	PE::World *World;								// Мир игры
	Player *Player;									// Игрок
	Background *Background;							// Фон
public:

};

#endif /*_GWORLD_H_*/