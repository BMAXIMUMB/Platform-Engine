// entity.h

#include "../main.h"
#include "score.h"

#ifndef _ENTITY_H_
#define _ENTITY_H_

struct entitysettings
{
	float spawnPosX					= NULL,
	spawnPosY						= NULL,
	sizeX							= NULL,
	sizeY							= NULL;

	PE::CSprite *sprite				= NULL;
	color4 color;
};

struct entitymoveinfo
{
	float speedX,
	speedY,
	accX,
	accY;
};

class CEntity
{
protected:

	float posX,
		posY,
		sizeX,
		sizeY;

	PE::CQuad *object;
	PE::CWorld *world;
	PE::CSprite *sprite;
	color4 color;

public:

	CEntity();
	~CEntity();

	void Delete(void);
	PE::CQuad* GetObjectID(void);

	void SetPosition(float x, float y);
	void GetPosition(float &x, float &y);
	void SetColor(color4 color);

	virtual void Create(PE::CWorld *world, entitysettings entity_settings) = 0;
};

////////////////////////////////////////////////////////////////////

// Класс игрока
class CPlayer :public CEntity
{
private:

	float spawnPosX;
	float spawnPosY;

	float startPosX;

	CScore *score;

public:

	CPlayer();
	~CPlayer();

	void Create(PE::CWorld *world, entitysettings player_settings);
	void SetSpawnPosition(float pos_x, float pos_y);
	void GetSpeed(float &x, float &y);
	bool onGround(void);
	void Spawn(void);
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
	CBlock();
	~CBlock();

	void Create(PE::CWorld *world, entitysettings block_settings);
};

#endif /*_ENTITY_H_*/