// background.cpp

#include "background.h"
#include "column_manager.h"

//----------------------------------------------------------------------------------------------------------

CBackground::CBackground(PE::CWorld *world)
{
	this->world = world;

	ColumnManager = new CColumnManager(world);

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

/////////////////////////////////////////////////////////////////////////////////////////////////

void CBackground::CreateGround()
{
	LayerObjectSettings los;

	los.positionSet = LAYER_POSITION_UNFIXED;
	los.moveMode = LAYER_MOVE_MODE_1;
	los.sizeX = GROUND_ELEMENT_SIZE_X;
	los.sizeY = GROUND_ELEMENT_SIZE_Y;
	los.sprite = world->GetApp()->spriteManager->Get("s_ground");
	los.color = {1, 1, 1, 1};

	// create ground
	for(int i = 1; i < GROUND_ELEMENT_COUNT + 1; i++)
	{
		los.posX = (float)GROUND_ELEMENT_SIZE_X / 2 + (GROUND_ELEMENT_SIZE_X*i) + START_ELEMENT_POS;
		los.posY = (float)150 / 2;

		groundElementList.push_back(CreateElement(los));
	}
}

void CBackground::ResetGround()
{
	for(int i = 0; i < GROUND_ELEMENT_COUNT; i++)
	{
		groundElementList[i]->SetPosition((float)GROUND_ELEMENT_SIZE_X / 2 + (GROUND_ELEMENT_SIZE_X*(i + 1)) +START_ELEMENT_POS, (float)150 / 2);
	}
}

void CBackground::DeleteGround()
{
	for(auto it = groundElementList.begin(); it != groundElementList.end(); it++)
	{
		DestroyElement(*it);
	}
	
	groundElementList.clear();
}

void CBackground::CheckGround()
{
	if(groundElementList.size())
	{
		float elempos[2], elemsize[2];
		float campos[2];
		int wsize[2];

		world->camera->GetPosition(campos[0], campos[1]);
		world->GetApp()->GetWindowSize(wsize[0], wsize[1]);

		groundElementList[0]->GetPosition(elempos[0], elempos[1]);
		groundElementList[0]->GetSize(elemsize[0], elemsize[1]);

		/*if(elempos[0] - (elemsize[0] / 2) + (wsize[0]*1.5) - campos[0] > 1280){

		printf("SPARTA\n");
		}*/

		for(unsigned int i = 0; i < groundElementList.size(); i++)
		{
			groundElementList[i]->GetPosition(elempos[0], elempos[1]);
			groundElementList[i]->GetSize(elemsize[0], elemsize[1]);

			// Если объект ушел за левую часть экрана
			if(elempos[0] + (elemsize[0] / 2) + (wsize[0] / 2) - campos[0] + world->camera->offsetX < 0)
			{
				// Переместим его в конец списка
				auto it = groundElementList.begin();
				//Ground[i]->Delete();
				//delete Ground[i];
				float np[2];

				groundElementList.back()->GetPosition(np[0], np[1]);
				groundElementList[i]->SetPosition(np[0] + elemsize[0], np[1]);

				CBackgroundElement *bge = groundElementList[i];	// Есть другой способ это сделать?

				groundElementList.erase(it + i);
				groundElementList.push_back(bge);
				//return;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void CBackground::CreateSky()
{
	LayerObjectSettings los;

	//	create sky
	los.positionSet = LAYER_POSITION_FIXED;
	los.moveMode = LAYER_MOVE_MODE_1;
	los.sizeX = 1280;
	los.sizeY = 720;
	los.sprite = world->GetApp()->spriteManager->Get("s_bg");
	los.color = 0xffffffff;
	los.posX = 1280 / 2;
	los.posY = 720 / 2;
	los.depth = -200;
	sky = CreateElement(los);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void CBackground::CreateColumn()
{
	ColumnManager->Create();
}

void CBackground::ResetColumn()
{
	ColumnManager->DeleteAll();
	ColumnManager->Create();
}

void CBackground::CheckColumn()
{
	ColumnManager->Check();
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void CBackground::Create()
{
	CreateSky();
	CreateGround();
	CreateColumn();
	setCreate(true);
}

void CBackground::Reset()
{
	world->background->Reset();
	
	ResetGround();
	ResetColumn();
}

void CBackground::Check()
{
	if(isCreate())
	{
		CheckGround();
		CheckColumn();
	}
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////

CBackgroundElement::CBackgroundElement()
{
	layerObject = nullptr;
}

CBackgroundElement::~CBackgroundElement()
{
	if(layerObject != nullptr) world->background->DestroyElement(layerObject);
}

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

/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
