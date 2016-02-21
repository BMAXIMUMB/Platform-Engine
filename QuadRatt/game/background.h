// background.h

#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "../main.h"

class CBackgroundElement
{
private:

	PE::CLayerObject *layerObject;
	PE::CWorld *world;

public:
	void Create(PE::CWorld *world, LayerObjectSettings los);
	void Delete();
	void GetPosition(float &x, float &y);
	void GetSize(float &x, float &y);
	void SetPosition(float x, float y);
};

class CBackground
{
private:

	std::vector<CBackgroundElement*> elementList;
	CBackgroundElement *sky;

	PE::CWorld *world;

	bool create;

	void CreateGround(PE::CApplication *App);
	void CreateSky(PE::CApplication *App);
	void CheckGround(PE::CCamera *Cam, PE::CApplication *App);

	bool isCreate(void){ return create; }
	void setCreate(bool val){ create = val; }

public:

	CBackground(PE::CWorld *world);
	~CBackground();

	CBackgroundElement* CreateElement(LayerObjectSettings los);
	void DestroyElement(CBackgroundElement *bElem);
	void Create(PE::CApplication *App);				

	void Check(PE::CCamera *Cam, PE::CApplication *App);											
};	

#endif /*_BACKGROUND_H_*/