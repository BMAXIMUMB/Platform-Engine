// layer.cpp

#include "layer.h"

namespace PlatformEngine
{
	CLayerObject::CLayerObject(LayerObjectSettings LOSettings)
	{
		posX = LOSettings.posX;
		posY = LOSettings.posY;
		sizeX = LOSettings.sizeX;
		sizeY = LOSettings.sizeY;
		depth = LOSettings.depth;
		pset = LOSettings.positionSet;
		sprite = LOSettings.sprite;
		moveFactor = LOSettings.moveFactor;
		moveMode = LOSettings.moveMode;
		color = LOSettings.color;
	}

	CLayerObject::~CLayerObject()
	{

	}

	void CLayerObject::GetPosition(float &x, float &y)
	{
		x = posX;
		y = posY;
	}

	void CLayerObject::GetSize(float &x, float &y)
	{
		x = sizeX;
		y = sizeY;
	}

	void CLayerObject::SetPosition(float x, float y)
	{
		posX = x;
		posY = y;
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////


	void CLayer::Sort()
	{
		CLayerObjectSort los;
		std::sort(lObjectList.begin(), lObjectList.end(), los);
	}

	CLayerObject* CLayer::CreateElement(LayerObjectSettings LOSettings)
	{
		CLayerObject *lo = new PlatformEngine::CLayerObject(LOSettings);

		AddElementToList(lo);
		Sort();

		return lo;
	}

	void CLayer::DestroyElement(CLayerObject *lo)
	{
		if(DeleteElementToList(lo))
		{
			delete lo;
		}
	}


	CLayer::CLayer()
	{
		oldposX = 0.0;
		oldposY = 0.0;
	}

	void CLayer::AddElementToList(CLayerObject *lo)
	{
		lObjectList.push_back(lo);
	}

	bool CLayer::DeleteElementToList(CLayerObject *lo)
	{
		for(auto it = lObjectList.begin(); it != lObjectList.end(); it++)
		{
			if(*it == lo)
			{
				lObjectList.erase(it);
				return true;
			}
		}
		return false;
	}

	void CLayer::Draw(CApplication *App, CCamera *Cam)
	{
		float cpos[2];
		Cam->GetPosition(cpos[0], cpos[1]);

		float cpd[2];
		cpd[0] = cpos[0] - oldposX;
		cpd[1] = cpos[1] - oldposY;

		for(unsigned int i = 0; i < lObjectList.size(); i++)
		{
			if(lObjectList[i]->pset == LAYER_POSITION_FIXED)
			{
				if(lObjectList[i]->sprite != nullptr)
				{
					SpriteDrawSettings sds;

					sds.Cam = nullptr;
					sds.posX = lObjectList[i]->posX;
					sds.posY = lObjectList[i]->posY;
					sds.sizeX = lObjectList[i]->sizeX;
					sds.sizeY = lObjectList[i]->sizeY;
					sds.cmultiple[0] = lObjectList[i]->color.r;
					sds.cmultiple[1] = lObjectList[i]->color.g;
					sds.cmultiple[2] = lObjectList[i]->color.b;
					sds.cmultiple[3] = lObjectList[i]->color.a;
					lObjectList[i]->sprite->Draw(App, sds);
				}
			}
			else
			{
				if(lObjectList[i]->sprite != nullptr)
				{
					SpriteDrawSettings sds;

					sds.posX = lObjectList[i]->posX;
					sds.posY = lObjectList[i]->posY;
					sds.sizeX = lObjectList[i]->sizeX;
					sds.sizeY = lObjectList[i]->sizeY;
					sds.cmultiple[0] = lObjectList[i]->color.r;
					sds.cmultiple[1] = lObjectList[i]->color.g;
					sds.cmultiple[2] = lObjectList[i]->color.b;
					sds.cmultiple[3] = lObjectList[i]->color.a;

					if(lObjectList[i]->moveMode == LAYER_MOVE_MODE_1)
					{
						sds.Cam = Cam;
						lObjectList[i]->sprite->Draw(App, sds);
					}

					else if(lObjectList[i]->moveMode == LAYER_MOVE_MODE_2)
					{
						lObjectList[i]->posX -= (cpos[0] - oldposX)*lObjectList[i]->moveFactor;
						lObjectList[i]->posY -= (cpos[1] - oldposY)*lObjectList[i]->moveFactor;
						lObjectList[i]->sprite->Draw(App, sds);
					}
				}
			}
		}

		oldposX = cpos[0];
		oldposY = cpos[1];
	}
};