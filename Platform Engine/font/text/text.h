// text.h
#pragma once

#include "../font.h"
#include "../../platform_engine.h"
#include <vector>

struct TextSettings
{
	PE::Font *Font			= NULL;
	int fontsize			= 12,
		fontdepth			= 16;
	float pos_x				= 0.0f,
		pos_y				= 0.0f;
	float colorR			= 0.0f,
		colorG				= 0.0f,
		colorB				= 0.0f,
		colorA				= 0.0f;
	wchar_t *text			= L"";
};

namespace PlatformEngine
{
	class Application;
	class Text
	{
	private:
		Font *F;
		wchar_t *text;
		int fontsize;
		int fontdepth;
		float color[4];
		float pos_x,
			pos_y;
		Application	*App;
	public:
		PLATFORMENGINE_API	Text(Application *App, TextSettings TSettings);
		PLATFORMENGINE_API	~Text();

		PLATFORMENGINE_API	void SetText(wchar_t *text);
		PLATFORMENGINE_API	void SetFontsize(int size);
		PLATFORMENGINE_API	void Render(void);
		PLATFORMENGINE_API	void Show(void);
	};

	class TextManager
	{
	private:
		std::vector< PlatformEngine::Text*> TextList;
	public:
		PLATFORMENGINE_API	void AddToList(Text *Text);
		PLATFORMENGINE_API	void Delete(Text *Text);

		PLATFORMENGINE_API	void Draw(void);
	};
};