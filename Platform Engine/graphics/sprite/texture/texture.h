// texture.h

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#define TGA_RGB			2
#define TGA_A			3
#define TGA_RLE			10

#define BUILD_MIPMAP

namespace PlatformEngine
{
	// ��������� TGA �����������
	struct ImageTGA
	{
		int channels;
		int sizeX;
		int sizeY;
		unsigned char * data;
		int bpp;
	};

	// CTextureImage
	// ����� ��������� �������� � ����������
	// �� ������ ������ �������������� ������ TGA ������ �������
	class CTextureImage
	{
	public:
		ImageTGA * tgaTexture;							// TGA ��������
		unsigned int textureID;							// ID ��������
		int textureType;								// ��� ��������(RGB, RGBA)

		void LoadFromFileTGA(const char * strfilename);	// �������� ��������
		ImageTGA * LoadTga(const char * strfilename);	// �������� �������� TGA

		CTextureImage();
		~CTextureImage();
	};
};

#endif //_TEXTURE_H_