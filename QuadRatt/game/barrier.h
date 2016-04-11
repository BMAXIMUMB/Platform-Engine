// barrier.h

#ifndef _BARRIER_H_
#define _BARRIER_H_

#include <vector>
#include "entity.h"
#include "../main.h"

//----------------------------------------------------------------------------------------------------------

struct beinfo
{
	float posX,
	posY,
	sizeX,
	sizeY;
	PE::CSprite *sprite;
};

class CBarrierElement
{
private:

	PE::CSprite *sprite;
	float posX,
		posY,
		sizeX,
		sizeY;

public:
	CBarrierElement(float px, float py, float sx, float sy, PE::CSprite *Spr);
	~CBarrierElement();

	beinfo GetInfo(void);
};

class CBarrierInfo
{
	friend class CBarrier;

private:

	std::vector<CBarrierElement*> elementList;

	float sizeX;


public:

	CBarrierInfo();
	~CBarrierInfo();

	bool LoadFromFile(const char *path, PE::CSpriteManager *SM);

	float GetSize(void);
};

class CBarrier
{
private:

	CBarrierInfo *barrierInfo;
	std::vector<CBlock*> blockList;

	float offset;

public:
	~CBarrier();
	void Create(PE::CWorld *world, CBarrierInfo *Binfo, float offset_x);
	void Destroy(void);
	void CreateElement(PE::CWorld *world, CBarrierElement *be, float offset_x);
	float GetOffset(void);
	float GetSize(void);
};

#endif /*_BARRIER_H_*/