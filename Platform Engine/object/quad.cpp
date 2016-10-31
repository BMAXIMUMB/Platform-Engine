/// quad.cpp

#include "quad.h"

namespace PlatformEngine
{
	CQuad::CQuad()
	{

	}

	CQuad::~CQuad()
	{

	}

	void CQuad::Create(PlatformEngine::CWorld *World, float posX, float posY, float sizeX, float sizeY, CSprite * sprite)
	{
		CObject::posX = posX;
		CObject::posY = posY;
		CObject::sizeX = sizeX;
		CObject::sizeY = sizeY;
		CObject::sprite = sprite;
		CObject::rotate = 0.0f;
		CObject::objectTypeForm = OBJECT_TYPE_QUAD;
		CObject::world = World;
	}
};