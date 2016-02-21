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

	class CSprite :public �Resource
	{
	public:
		CTexCoord2f *texCoord;			// ���������� ����������
		CTextureImage *texture;			// �������� �������
		CVbo *vbo;										// VBO

	public:
		PLATFORMENGINE_API CSprite();										// �����������
		PLATFORMENGINE_API ~CSprite();										// ����������

		PLATFORMENGINE_API bool LoadFromFile(const char * path);			// �������� ������� �� �����
		PLATFORMENGINE_API void Draw(PlatformEngine::CApplication *app, SpriteDrawSettings sds);	// ���������� ������
	};

	class Lines :public CSprite
	{

	};
}

#endif //___sprite_h___