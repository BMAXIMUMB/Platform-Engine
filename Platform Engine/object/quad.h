// quad.h

#ifndef _QUAD_H_
#define _QUAD_H_

#include "object.h"

namespace PlatformEngine
{
	class CQuad : public CObject
	{

	public:
		PLATFORMENGINE_API	CQuad();
		PLATFORMENGINE_API	~CQuad();
		PLATFORMENGINE_API	void Create(PlatformEngine::CWorld *World, float posX, float posY, float sizeX, float sizeY, CSprite * sprite);
	};
};

#endif //___quad_h___