// texture.cpp

#include "texture.h"
#include "../../../platform_engine.h"
#include <string>

extern void logprintf(std::string str);

namespace PlatformEngine
{
	CTextureImage::CTextureImage()
	{

	}

	CTextureImage::~CTextureImage()
	{

	}

	void CTextureImage::LoadFromFileTGA(const char * strfilename)
	{
		tgaTexture = LoadTga(strfilename);
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		if(tgaTexture->channels == 4) textureType = GL_RGBA;
		else textureType = GL_RGB;

		gluBuild2DMipmaps(GL_TEXTURE_2D, tgaTexture->channels,
			tgaTexture->sizeX,
			tgaTexture->sizeY,
			textureType, GL_UNSIGNED_BYTE,
			tgaTexture->data);
		//glTexImage2D(GL_TEXTURE_2D, 0, tga_texture->channels, tga_texture->sizeX, tga_texture->sizeY, 0, textype, GL_UNSIGNED_BYTE, tga_texture->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		
		delete[] tgaTexture->data;
		delete tgaTexture;
	}

	ImageTGA* CTextureImage::LoadTga(const char * strfilename)
	{
		ImageTGA *pImgData = NULL;
		FILE *pFile = NULL;
		WORD width = 0;
		WORD height = 0;
		byte length = 0;
		byte imgType = 0;
		byte bits = 0;
		int channels = 0;
		int stride = 0;
		int i = 0;

		pFile = fopen(strfilename, "rb");
		if(pFile == NULL)
		{
			logprintf("Файл не найден: " + (std::string)strfilename);
			return NULL;
		}

		pImgData = (ImageTGA*)malloc(sizeof(ImageTGA));

		fread(&length, sizeof(byte), 1, pFile);

		fseek(pFile, 1, SEEK_CUR);

		fread(&imgType, sizeof(byte), 1, pFile);

		fseek(pFile, 9, SEEK_CUR);

		fread(&width, sizeof(WORD), 1, pFile);
		fread(&height, sizeof(WORD), 1, pFile);
		fread(&bits, sizeof(byte), 1, pFile);

		fseek(pFile, length + 1, SEEK_CUR);

		if(imgType != TGA_RLE)
		{
			// Check for 24 or 32 Bit
			if(bits == 24 || bits == 32)
			{
				channels = bits / 8;
				stride = channels * width;
				pImgData->data = new unsigned char[stride * height];

				for(int y = 0; y < height; y++)
				{
					unsigned char *pLine = &(pImgData->data[stride * y]);

					fread(pLine, stride, 1, pFile);

					for(i = 0; i < stride; i += channels)
					{
						int temp = pLine[i];
						pLine[i] = pLine[i + 2];
						pLine[i + 2] = temp;
					}
				}
			}

			// Check for 16 Bit
			else if(bits == 16)
			{
				unsigned short pixels = 0;
				int r = 0, g = 0, b = 0;

				channels = 3;
				stride = channels * width;
				pImgData->data = new unsigned char[stride * height];

				for(int i = 0; i < width*height; i++)
				{
					fread(&pixels, sizeof(unsigned short), 1, pFile);

					b = (pixels & 0x1f) << 3;
					g = ((pixels >> 5) & 0x1f) << 3;
					r = ((pixels >> 10) & 0x1f) << 3;

					pImgData->data[i * 3 + 0] = r;
					pImgData->data[i * 3 + 1] = g;
					pImgData->data[i * 3 + 2] = b;
				}
			}

			else
				return NULL;
		}

		else
		{
			byte rleID = 0;
			int colorsRead = 0;
			channels = bits / 8;
			stride = channels * width;

			pImgData->data = new unsigned char[stride * height];
			byte *pColors = new byte[channels];

			while(i < width*height)
			{

				fread(&rleID, sizeof(byte), 1, pFile);


				if(rleID < 128)
				{
					rleID++;

					while(rleID)
					{
						fread(pColors, sizeof(byte)* channels, 1, pFile);

						pImgData->data[colorsRead + 0] = pColors[2];
						pImgData->data[colorsRead + 1] = pColors[1];
						pImgData->data[colorsRead + 2] = pColors[0];

						if(bits == 32)	pImgData->data[colorsRead + 3] = pColors[3];

						i++;
						rleID--;
						colorsRead += channels;
					}
				}

				else
				{
					rleID -= 127;

					fread(pColors, sizeof(byte)* channels, 1, pFile);

					while(rleID)
					{
						pImgData->data[colorsRead + 0] = pColors[2];
						pImgData->data[colorsRead + 1] = pColors[1];
						pImgData->data[colorsRead + 2] = pColors[0];

						if(bits == 32)	pImgData->data[colorsRead + 3] = pColors[3];

						i++;
						rleID--;
						colorsRead += channels;
					}
				}
			}
			delete[] pColors;
		}

		fclose(pFile);


		pImgData->channels = channels;
		pImgData->sizeX = width;
		pImgData->sizeY = height;

		return pImgData;
	}
};