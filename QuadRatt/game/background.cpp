// background.cpp

#include "background.h"

CBackground::CBackground(PE::CWorld *world)
{
	this->world = world;
	setCreate(false);
}

CBackground::~CBackground() {}

CBackgroundElement* CBackground::CreateElement(LayerObjectSettings los)
{
	CBackgroundElement * elem = new CBackgroundElement;
	elem->Create(world, los);

	return elem;
}

void CBackground::DestroyElement(CBackgroundElement *bElem)
{
	bElem->Delete();
	delete bElem;
}

void CBackground::CreateGround(PE::CApplication *App)
{
	LayerObjectSettings los;

	los.positionSet = LAYER_POSITION_UNFIXED;
	los.moveMode = LAYER_MOVE_MODE_1;
	los.sizeX = GROUND_ELEMENT_SIZE_X;
	los.sizeY = GROUND_ELEMENT_SIZE_Y;
	los.sprite = App->spriteManager->Get("s_ground");
	los.color = {1, 1, 1, 1};

	// create ground
	for(int i = 1; i < GROUND_ELEMENT_COUNT + 1; i++)
	{
		los.posX = (float)GROUND_ELEMENT_SIZE_X / 2 + (GROUND_ELEMENT_SIZE_X*i) + START_ELEMENT_POS;
		los.posY = (float)150 / 2;
		elementList.push_back(CreateElement(los));
	}
}

void CBackground::CreateSky(PE::CApplication *App)
{
	LayerObjectSettings los;

	//	create sky
	los.positionSet = LAYER_POSITION_FIXED;
	los.moveMode = LAYER_MOVE_MODE_1;
	los.sizeX = 1280;
	los.sizeY = 720;
	los.sprite = App->spriteManager->Get("s_bg");
	los.color = {1, 1, 1, 1.0};
	los.posX = 1280 / 2;
	los.posY = 720 / 2;
	sky = CreateElement(los);
}

void CBackground::Create(PE::CApplication *App)
{
	CreateSky(App);
	CreateGround(App);
	setCreate(true);
}

void CBackground::Check(PE::CCamera *Cam, PE::CApplication *App)
{
	if(isCreate())
	{
		CheckGround(Cam, App);
	}
	
}

void CBackground::CheckGround(PE::CCamera *Cam, PE::CApplication *App)
{
	float elempos[2], elemsize[2];
	float campos[2];
	int wsize[2];

	Cam->GetPosition(campos[0], campos[1]);
	App->GetWindowSize(wsize[0], wsize[1]);

	elementList[0]->GetPosition(elempos[0], elempos[1]);
	elementList[0]->GetSize(elemsize[0], elemsize[1]);

	/*if(elempos[0] - (elemsize[0] / 2) + (wsize[0]*1.5) - campos[0] > 1280){

		printf("SPARTA\n");
	}*/

	for(unsigned int i = 0; i < elementList.size(); i++)
	{
		elementList[i]->GetPosition(elempos[0], elempos[1]);
		elementList[i]->GetSize(elemsize[0], elemsize[1]);

		// Если объект ушел за левую часть экрана
		if(elempos[0] + (elemsize[0] / 2) +  (wsize[0] / 2) - campos[0]+Cam->offsetX < 0)
		{	
			// Переместим его в конец списка
			auto it = elementList.begin();
			//Ground[i]->Delete();
			//delete Ground[i];
			float np[2];

			elementList.back()->GetPosition(np[0], np[1]);
			elementList[i]->SetPosition(np[0] + elemsize[0] , np[1]);

			CBackgroundElement *bge = elementList[i];	// Есть другой способ это сделать?

			elementList.erase(it + i);
			elementList.push_back(bge);
			//return;
		}
	}
}

////////////////////////////////////////////////////////////////////////////

void CBackgroundElement::Create(PE::CWorld *world, LayerObjectSettings los)
{
	this->world = world;
	layerObject = this->world->background->CreateElement(los);
}

void CBackgroundElement::Delete()
{
	world->background->DestroyElement(layerObject);
}

void CBackgroundElement::GetPosition(float &x, float &y)
{
	layerObject->GetPosition(x, y);
}

void CBackgroundElement::GetSize(float &x, float &y)
{
	layerObject->GetSize(x, y);
}

void CBackgroundElement::SetPosition(float x, float y)
{
	layerObject->SetPosition(x, y);
}