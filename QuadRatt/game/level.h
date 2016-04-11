// level.h

#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "../main.h"
#include "background.h"
#include "barrier.h"

//----------------------------------------------------------------------------------------------------------

class CPlayer;
class CGame;

class CLevel
{
private:

	CBackground *background;
	CPlayer *player;
	CGame *game;

	PE::CWorld *world;
	PE::CApplication *app;
	PE::CParticleEmitter *particleEmitter;

	std::vector<CBarrierInfo*> barrierInfoList;		// Шаблоны препятствий
	std::vector<CBarrier*> barrierList;				// Сами препятствия

public:

	CLevel(CGame *game);
	~CLevel();

	void Create(void);
	void Start(void);
	void Restart(void);

	void PlayerCreate(void);
	void Update(void);

	void BarrierGenerate(float offset);
	void StartBarrierGenerate(void);
	void BarrierDelete(CBarrier *Barrier);
	void LoadBarrierInfo(void);
	void BarrierCheck(void);
	CBarrierInfo* LoadBarrierInfoFromFile(const char *path);

	CBackground* GetBackground(void);
	CPlayer* GetPlayer(void);

	void CreateBackground(void);
	void CheckBackground(void);
};

#endif /*_LEVEL_H_*/