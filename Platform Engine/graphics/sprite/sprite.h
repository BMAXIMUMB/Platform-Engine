// sprite.h

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "../vertex/vertex.h"
#include "texture\texture.h"
#include "../vbo/vbo.h"
#include "../../application/file/file.h"
#include "../../platform_engine.h"
#include "../../world/camera/camera.h"
#include "../../resource/resource.h"

struct SpriteDrawSettings
{
	float posX,
	posY,
	sizeX,
	sizeY,
	rot						= 0;
	PE::CCamera *Cam		= nullptr;
	float cmultiple[4];
};

namespace PlatformEngine
{
	class CApplication;

	class CSprite :public СResource
	{
	public:
		CTexCoord2f *texCoord;			// Текстурные координаты
		CTextureImage *texture;			// Текстура спрайта
		CVbo *vbo;										// VBO

	public:
		PLATFORMENGINE_API CSprite();										// Конструктор
		PLATFORMENGINE_API ~CSprite();										// Деструктор

		PLATFORMENGINE_API bool LoadFromFile(const char * path);			// Загрузка спрайта из файла
		PLATFORMENGINE_API void Draw(PlatformEngine::CApplication *app, SpriteDrawSettings sds);	// Отрисовать спрайт
	};

	class Lines :public CSprite
	{

	};
}

#endif //___sprite_h___