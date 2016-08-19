// entity.h

#include "../main.h"
#include "score.h"

#ifndef _ENTITY_H_
#define _ENTITY_H_

// Эта структура хранит параметры объекта
struct EntityOptions
{
	// Стартовая позиция по X и Y
	float spawnPosX					= NULL;
	float spawnPosY					= NULL;

	// Размеры по X и Y
	float sizeX						= NULL;
	float sizeY						= NULL;

	// Спрайт объекта
	PlatformEngine::CSprite *sprite	= NULL;

	// Цвет объекта. Изначально равен 255.255.255.255 (RGBA).
	color4 color					= Color(0xffffffff);
};

class CEntity
{
protected:

	EntityOptions options;

	PlatformEngine::CQuad *object;
	PlatformEngine::CWorld *world;

public:

	CEntity(PlatformEngine::CWorld *world);
	~CEntity();

	void Delete(void);
	PlatformEngine::CQuad* GetObjectID(void);

	void SetPosition(float x, float y);
	void SetColor(color4 color);

	void GetPosition(float &x, float &y);
	void GetSize(float &x, float &y);

	virtual void Create(float posX, float posY) = 0;
};

////////////////////////////////////////////////////////////////////

// Класс игрока
class CPlayer :public CEntity
{
private:

	float startPosX;

	CScore *score;

public:

	CPlayer(PlatformEngine::CWorld *world);
	~CPlayer();

	void Create(float posX, float posY);
	void SetSpawnPosition(float pos_x, float pos_y);
	void GetSpeed(float &x, float &y);
	bool onGround(void);
	void Spawn(void);
	void Respawn(void);
	void Reset(void);
	void Move(float speed_x, float speed_y);
	void Jump(void);

	float GetStartPos(void){ return startPosX; }
	void SetStartPos(float value);
	void SetStartPos(void);

	int GetScore(void);
	int GetBestScore(void);
	void UpdateScore(void);
};

////////////////////////////////////////////////////////////////////

class CBlock :public CEntity
{
public:
	CBlock(PlatformEngine::CWorld *world);
	~CBlock();

	void Create(float posX, float posY);
};

#endif /*_ENTITY_H_*/