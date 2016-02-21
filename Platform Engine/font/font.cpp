// font.cpp

#include "font.h"

namespace PlatformEngine
{
	CFont::CFont()
	{
		//FTF = NULL;
	}

	CFont::CFont(const CFont& f)
	{
		
	}

	CFont::~CFont()
	{
		// ׃האכטל רנטפע
		if(ftf != NULL) delete ftf;
	}

	bool CFont::Load(char *ttf)
	{
		ftf = new FTGLBitmapFont(ttf);
		ftf->CharMap(ft_encoding_unicode);

		return true;
	}

	void CFont::SetSize(int size)
	{
		this->size = size;
		ftf->FaceSize(size);
	}

	void CFont::SetDepth(int depth)
	{
		this->depth = depth;
		ftf->Depth(depth);
	}

	void CFont::Render(float posx, float posy, const wchar_t* text)
	{
		glRasterPos2f(posx, posy);
		ftf->Render(text);
	}

	int CFont::GetSize()
	{
		return size;
	}
};