// level.h

#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "../main.h"
#include "background.h"
#include "barrier.h"

class CPlayer;
class CLevel
{
private:

	CBackground *background;
	CPlayer *player;

	PE::CWorld *world;
	PE::CApplication *app;
	PE::CParticleEmitter *particleEmitter;

	std::vector<CBarrierInfo*> barrierInfoList;		// ������� �����������
	std::vector<CBarrier*> barrierList;				// ���� �����������

public:

	CLevel(PE::CWorld *world, PE::CApplication *app);
	~CLevel();

	void Start(void);

	void PlayerCreate(void);
	void Update(void);

	void BarrierGenerate(float offset);
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