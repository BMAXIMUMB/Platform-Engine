// gui.cpp

#include "gui.h"
#include "gui_manager.h"
#include "../font/font.h"

#include <atlbase.h>

namespace Gui
{
	CGuiElement::CGuiElement()
	{
		showed				= false;
		clicked				= false;
		alphaStep			= 0.0f;
		alphaSset			= false;
		moving				= false;
		scaling				= false;
		atime				= 0.0f;
		acurtime			= 0.0f;
	}

	CGuiElement::~CGuiElement()
	{
		GUI->ElementDeleteToList(this);
	}

	void CGuiElement::Show()
	{
		showed = true;
	}

	void CGuiElement::Hide()
	{
		showed = false;
	}

	void CGuiElement::Create(CGuiManager *GUI, GuiElementSettings ges)
	{
		this->posX = ges.posX;
		this->posY = ges.posY;
		this->sizeX = ges.sizeX;
		this->sizeY = ges.sizeY;
		this->name = ges.name;
		this->sprite = ges.sprite;
		this->color = ges.color;
		this->GUI = GUI;

		GUI->ElementAddToList(this);
	}

	void CGuiElement::GetPosition(float &x, float &y)
	{
		x = posX;
		y = posY;
	}

	void CGuiElement::GetSize(float &x, float &y)
	{
		x = sizeX;
		y = sizeY;
	}

	void CGuiElement::SetAlpha(float alpha)
	{
		color.a = alpha;
	}

	void CGuiElement::SetAlphaSmooth(float alpha, float time)
	{
		atime = time;
		acurtime = 0;
		galpha = alpha;
		alphaSset = true;
		alphaStep = (alpha - color.a) / time;
	}

	void CGuiElement::Move(float px, float py, float time)
	{
		mtime = time;
		mcurtime = 0;
		posStep[0] = (px - posX) / time;
		posStep[1] = (py - posY) / time;
		gpos[0] = px, gpos[1] = py;
		moving = true;
	}

	void CGuiElement::SetScaleSmooth(float scale, float time)
	{
		stime = time;
		scurtime = 0;
		gscale[0] = sizeX*(scale);
		gscale[1] = sizeY*(scale);
		scaleStep[0] = (gscale[0] - sizeX) / time;
		scaleStep[1] = (gscale[1] - sizeY) / time;
		scaling = true;
	}

	void CGuiElement::Render()
	{
		if(sprite != nullptr)
		{
			// Получаем данные для рендера
			SpriteDrawSettings sds;

			sds.posX = posX;
			sds.posY = posY;
			sds.sizeX = sizeX;
			sds.sizeY = sizeY;
			sds.rot = 0;
			sds.cmultiple[0] = color.r;
			sds.cmultiple[1] = color.g;
			sds.cmultiple[2] = color.b;
			sds.cmultiple[3] = color.a;

			// Рендерим
			sprite->Draw(GUI->app, sds);
		}
		
	}

	///////////////////////////////////////////////////////////////////////////////////

	void CBox::AttachElement(CGuiElement *Element)
	{
		elementList.push_back(Element);
	}

	void CBox::AttachElement(std::string name)
	{
		elementList.push_back(GUI->FindElement(name));
	}

	void CBox::DeattachElement(CGuiElement *Element)
	{
		for(auto it = elementList.begin(); it != elementList.end(); it++)
		{
			if(*it == Element)
			{
				elementList.erase(it);
				break;
			}
		}
	}

	void CBox::Show()
	{
		showed = true;

		for(unsigned int i = 0; i < elementList.size(); i++)
		{
			elementList[i]->showed = true;
		}
	}

	void CBox::Hide()
	{
		showed = false;

		for(unsigned int i = 0; i < elementList.size(); i++)
		{
			elementList[i]->showed = false;
		}
	}

	void CBox::SetAlpha(float alpha)
	{
		color.a = alpha;

		for(unsigned int i = 0; i < elementList.size(); i++)
		{
			elementList[i]->color.a = alpha;
		}
	}

	void CBox::SetAlphaSmooth(float alpha, float time)
	{
		atime = time;
		acurtime = 0;
		galpha = alpha;
		alphaSset = true;
		alphaStep = (alpha - color.a) / time;

		for(unsigned int i = 0; i < elementList.size(); i++)
		{
			elementList[i]->atime = time;
			elementList[i]->acurtime = 0;
			elementList[i]->galpha = alpha;
			elementList[i]->alphaSset = true;
			elementList[i]->alphaStep = (alpha - color.a) / time;
		}
	}

	void CBox::Move(float px, float py, float time)
	{
		mtime = time;
		mcurtime = 0;
		posStep[0] = (px - posX) / time;
		posStep[1] = (py - posY) / time;
		gpos[0] = px, gpos[1] = py;
		moving = true;

		for(unsigned int i = 0; i < elementList.size(); i++)
		{
			elementList[i]->mtime = time;
			elementList[i]->mcurtime = 0;
			elementList[i]->posStep[0] = (px - posX) / time;
			elementList[i]->posStep[1] = (py - posY) / time;
			elementList[i]->gpos[0] = px, gpos[1] = py;
			elementList[i]->moving = true;
		}
	}

	void CBox::SetScaleSmooth(float scale, float time)
	{
		stime = time;
		scurtime = 0;
		gscale[0] = sizeX*(scale);
		gscale[1] = sizeY*(scale);
		scaleStep[0] = (gscale[0] - sizeX) / time;
		scaleStep[1] = (gscale[1] - sizeY) / time;
		scaling = true;

		for(unsigned int i = 0; i < elementList.size(); i++)
		{
			elementList[i]->stime = time;
			elementList[i]->scurtime = 0;
			elementList[i]->gscale[0] = sizeX*(scale);
			elementList[i]->gscale[1] = sizeY*(scale);
			elementList[i]->scaleStep[0] = (gscale[0] - sizeX) / time;
			elementList[i]->scaleStep[1] = (gscale[1] - sizeY) / time;
			elementList[i]->scaling = true;
		}
	}

	//////////////////////////////////////////////////////////////////////////////
	CText::CText()
	{
		text = new wchar_t[50];
	}
	
	CText::~CText()
	{
		delete[] text;
	}

	void CText::Create(CGuiManager *GUI, TextSettings ts)
	{
		this->font = ts.font;
		this->fontsize = ts.fontsize;
		this->fontdepth = ts.fontdepth;
		this->posX = ts.posX;
		this->posY = ts.posY;
		this->color = ts.color;
		this->name = ts.name;
		this->GUI = GUI;
		this->align = ts.align;

		wcscpy(text, ts.text);

		this->font->SetSize(fontsize);
		this->font->SetDepth(fontdepth);

		GUI->ElementAddToList(this);
	}

	void CText::Render()
	{
		GUI->app->shaderFontDefault->Use();

		// Узнаем адрес юниформа для цвета
		GLuint cmul = GUI->GetApp()->shaderFontDefault->getUniformLocation("color");

		//
		int wsize[2];
		float wndpos[2];

		GUI->app->GetWindowSize(wsize[0], wsize[1]);

		float wwd[2] = {(float)wsize[0] / 2, (float)wsize[1] / 2};
		wndpos[0] = (1.0f / wwd[0])*posX;
		wndpos[0] -= 1.0f;
		wndpos[1] = (1.0f / wwd[1])*posY;
		wndpos[1] -= 1.0f;

		//glColor4f(color.r, color.g, color.b, color.a);
		GUI->GetApp()->shaderFontDefault->setUniform(cmul, color);
		
		// Выравниваем текст

		float offset[2] = {0.0f, 0.0f};

		if(align == ALIGN_LEFT)
		{
			offset[1] = -((font->GetHeight() / 2.0f) / wsize[1]);
		}
		else if(align == ALIGN_CENTER)
		{
			offset[1] = -((font->GetHeight() / 2.0f) / wsize[1]);
			offset[0] = -((font->GetWidth(text)) / wsize[0]);
		}
		else
		{
			offset[1] = -((font->GetHeight() / 2.0f) / wsize[1]);
			offset[0] = -((font->GetWidth(text))*2 / wsize[0]);
		}

		// Рендерим
		font->Render(wndpos[0] + offset[0], wndpos[1] + offset[1], text);
	}

	void CText::SetText(char *text)
	{
		USES_CONVERSION;

		if(wcscmp(this->text, A2W(text)))
		{
			wcscpy(this->text, A2W(text));
		}
	}

	void CText::SetText(wchar_t *text)
	{
		if(wcscmp(this->text, text))
		{
			wcscpy(this->text, text);
		}
	}

	void CText::SetFontsize(int size)
	{
		fontsize = size;
		font->SetSize(size);
	}
};