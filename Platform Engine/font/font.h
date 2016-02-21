// font.h

#ifndef _FONT_H_
#define _FONT_H_

#include "../resource/resource.h"
#include <string>

#include <ftgl/FTFont.h>
#include <ftgl/FTGLBitmapFont.h>
#include <ftgl/FTGLOutlineFont.h>
#include <ftgl/FTGLPixmapFont.h>
#include <ftgl/FTGLExtrdFont.h>

namespace PlatformEngine
{
	class CFont:public ÑResource
	{
	private:
		FTFont *ftf;
		int size;
		int depth;

	public:
		CFont();
		CFont(const CFont&);
		~CFont();

		bool Load(char *ttf);
		void SetSize(int size);
		void SetDepth(int depth); 
		void Render(float posx, float posy, const wchar_t* text);

		int GetSize(void);
	};
};

#endif //_FONT_H_