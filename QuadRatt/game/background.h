// background.h

#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "../main.h"

class CColumnManager;

struct ColumnSettings
{
	int depth;
	float posX;
	float sizeX;
	float sizeY;
};

class CBackgroundElement
{

protected:

	PE::CLayerObject *layerObject;
	PE::CWorld *world;

public:

	CBackgroundElement();
	~CBackgroundElement();

	void Create(PE::CWorld *world, LayerObjectSettings los);
	void Delete();
	void GetPosition(float &x, float &y);
	void GetSize(float &x, float &y);
	void SetPosition(float x, float y);

	PE::CLayerObject* GetLayerObject(void){ return layerObject; }

};

class CBackground
{

private:

	std::vector<CBackgroundElement*> groundElementList;
	CColumnManager *ColumnManager;

	CBackgroundElement *sky;

	PE::CWorld *world;

	bool create;

	void CreateColumn(void);
	void CreateGround(void);
	void CreateSky(void);

	void CheckGround(void);
	void CheckColumn(void);

	void ResetGround(void);
	void ResetColumn(void);

	void DeleteGround(void);

	bool isCreate(void){ return create; }
	void setCreate(bool val){ create = val; }

public:

	CBackground(PE::CWorld *world);
	~CBackground();

	CBackgroundElement* CreateElement(LayerObjectSettings los);
	void DestroyElement(CBackgroundElement *bElem);
	void Create(void);
	void Reset(void);

	void Check(void);

};	

#endif /*_BACKGROUND_H_*/