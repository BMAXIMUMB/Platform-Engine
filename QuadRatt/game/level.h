// level.h

#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "../main.h"
#include "background.h"
#include "map\map.h"

//----------------------------------------------------------------------------------------------------------

class CPlayer;
class CGame;

class CLevel
{
private:

	CBackground *background;
	CPlayer *player;
	CGame *game;
	CMap *map;

	PlatformEngine::CWorld *world;
	PlatformEngine::CApplication *app;
	PlatformEngine::CParticleEmitter *particleEmitter;

	float oldPosX;

public:

	CLevel(CGame *game);
	~CLevel();

	void Create(void);
	void Destroy(void);
	void Start(void);
	void Restart(void);

	void PlayerCreate(void);
	void LoopFunction(void);

	void CheckMap(void);
	void Check(void);

	CBackground* GetBackground(void);
	CPlayer* GetPlayer(void);
	CMap* GetMap(void);

	void CreateBackground(void);
	void CheckBackground(void);

	////////////////////
	bool oldPosCheck;
};

#endif /*_LEVEL_H_*/