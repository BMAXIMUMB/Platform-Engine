// layer.h

#ifndef _LAYER_H_
#define _LAYER_H_

#include "../graphics/sprite/sprite.h"
#include "../application/application.h"
#include <vector>

#define LAYER_POSITION_FIXED				(0x0)
#define LAYER_POSITION_UNFIXED				(0x1)

#define LAYER_MOVE_MODE_1					(0x0)
#define LAYER_MOVE_MODE_2					(0x1)

struct LayerObjectSettings
{
	float posX						= NULL;
	float posY						= NULL;
	float sizeX						= NULL;
	float sizeY						= NULL;

	unsigned int positionSet		= LAYER_POSITION_FIXED;
	unsigned int moveMode			= LAYER_MOVE_MODE_1;
	float moveFactor				= 1.0;

	PlatformEngine::CSprite *sprite	= nullptr;

	color4 color;
};

namespace PlatformEngine
{
	class CLayerObject
	{
		friend class CLayer;
		friend class ÑLayerScroll;

	private:

		float posX;
		float posY;
		float sizeX;
		float sizeY;

		unsigned int pset;
		unsigned int moveMode;
		float moveFactor;

		CSprite *sprite;
		color4 color;

	public:

		PLATFORMENGINE_API	CLayerObject(LayerObjectSettings LOSettings);
		PLATFORMENGINE_API	~CLayerObject();

		PLATFORMENGINE_API void GetPosition(float &x, float &y);
		PLATFORMENGINE_API void GetSize(float &x, float &y);

		PLATFORMENGINE_API void SetPosition(float x, float y);
	};

	class CLayer
	{
	protected:

		float oldposX;
		float oldposY;

		std::vector<PlatformEngine::CLayerObject*> lObjectList;

		void AddElementToList(CLayerObject *lo);
		bool DeleteElementToList(CLayerObject *lo);

	public:

		PLATFORMENGINE_API	CLayer();

		PLATFORMENGINE_API	CLayerObject* CreateElement(LayerObjectSettings LOSettings);

		PLATFORMENGINE_API	void DestroyElement(CLayerObject *lo);

		PLATFORMENGINE_API	void Draw(CApplication *App, CCamera *Cam);
	};
};

#endif //_LAYER_H_