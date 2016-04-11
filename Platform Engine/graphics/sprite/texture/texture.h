// texture.h

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#define TGA_RGB			2
#define TGA_A			3
#define TGA_RLE			10

#define BUILD_MIPMAP

namespace PlatformEngine
{
	// Структура TGA изображения
	struct ImageTGA
	{
		int channels;
		int sizeX;
		int sizeY;
		unsigned char * data;
		int bpp;
	};

	// CTextureImage
	// Класс позволяет работать с текстурами
	// На данный момент поддерживается только TGA формат текстур
	class CTextureImage
	{
	public:
		ImageTGA * tgaTexture;							// TGA текстура
		unsigned int textureID;							// ID текстуры
		int textureType;								// Тип текстуры(RGB, RGBA)

		void LoadFromFileTGA(const char * strfilename);	// Загрузка текстуры
		ImageTGA * LoadTga(const char * strfilename);	// Загрузка текстуры TGA

		CTextureImage();
		~CTextureImage();
	};
};

#endif //_TEXTURE_H_