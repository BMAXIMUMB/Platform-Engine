// text.cpp

#include "text.h"
#include "../../application/application.h"

namespace PlatformEngine
{
	Text::Text(Application *App, TextSettings TSettings)
	{
		text = TSettings.text;
		fontsize = TSettings.fontsize;
		fontdepth = TSettings.fontdepth;
		pos_x = TSettings.pos_x;
		pos_y = TSettings.pos_y;
		color[0] = TSettings.colorR;
		color[1] = TSettings.colorG;
		color[2] = TSettings.colorB;
		color[3] = TSettings.colorA;
		F = TSettings.Font;
		Text::App = App;

		F->SetSize(fontsize);
		F->SetDepth(fontdepth);
	}

	Text::~Text()
	{

	}

	void Text::SetText(wchar_t *text)
	{
		Text::text = text;
	}

	void Text::SetFontsize(int size)
	{
		fontsize = size;
		F->SetSize(size);
	}

	void Text::Render()
	{
		int wsize[2];
		float wndpos[2];
		App->GetWindowSize(wsize[0], wsize[1]);
		float wwd[2] = {(float)wsize[0] / 2, (float)wsize[1] / 2};
		wndpos[0] = (1.0f / wwd[0])*pos_x;
		wndpos[0] -= 1.0f;
		wndpos[1] = (1.0f / wwd[1])*pos_y;
		wndpos[1] -= 1.0f;
		glColor4f(color[0], color[1], color[2], color[3]);
		F->Render(wndpos[0], wndpos[1], text);
	}

	void Text::Show()
	{
		App->TextManager->AddToList(this);
	}

	//////////////////////////////////////////////////////////////////////////////////

	void TextManager::AddToList(Text *Text)
	{
		TextList.push_back(Text);
	}

	void TextManager::Delete(Text *Text)
	{
		for(auto it = TextList.begin(); it != TextList.end();)
		{
			if(*it == Text)
			{
				TextList.erase(it);
				break;
			}
		}
	}

	void TextManager::Draw()
	{
		for(unsigned int i = 0; i < TextList.size(); i++)
		{
			TextList[i]->Render();
		}
	}
};