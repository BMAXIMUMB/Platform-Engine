// gui.h

#ifndef _GUI_H_
#define _GUI_H_

#include <string>
#include "../application/application.h"

enum TextAlign
{
	ALIGN_CENTER,
	ALIGN_RIGHT,
	ALIGN_LEFT
};

struct GuiElementSettings
{
	float posX;
	float posY;
	float sizeX;
	float sizeY;

	PE::CSprite *sprite	= nullptr;
	std::string name;
	color4 color;
};

struct TextSettings
{
	int fontsize = 12;
	int fontdepth = 16;
	float posX = 0.0;
	float posY = 0.0f;

	wchar_t *text = L"";
	std::string name;
	color4 color;
	PE::CFont *font = nullptr;
	TextAlign align = ALIGN_LEFT;
};

namespace Gui
{
	class CGuiManager;
	class CBox;

	class CGuiElement	// basic element
	{
		friend class CGuiManager;
		friend class CBox;

	protected:
		float posX;
		float posY;
		float sizeX;
		float sizeY;

		std::string name;
		PE::CSprite *sprite;
		color4 color;

		bool showed;
		bool clicked;
		int clickedKey;

		CGuiManager *GUI;

		// alpha smooth settings
		float atime;
		float acurtime;
		float alphaStep;
		float galpha;
		bool alphaSset;

		// move settings
		float mtime;
		float mcurtime;
		float posStep[2];
		float gpos[2];
		bool moving;

		// scale settings;
		float stime;
		float scurtime;
		float scaleStep[2];
		float gscale[2];
		bool scaling;

		//
		PLATFORMENGINE_API virtual void Render(void);

	public:

		PLATFORMENGINE_API CGuiElement();
		PLATFORMENGINE_API ~CGuiElement();
		
		// Is...
		PLATFORMENGINE_API bool	IsShowed(void){ return showed; }
		PLATFORMENGINE_API bool IsClicked(void){ return clicked; }
		PLATFORMENGINE_API bool IsMoving(void) { return moving; }
		PLATFORMENGINE_API bool IsScaling(void){ return scaling; }
		PLATFORMENGINE_API bool IsAlphaSmooth(void){ return alphaSset; }


		PLATFORMENGINE_API std::string GetName(void){ return name; }
		PLATFORMENGINE_API PE::CSprite* GetSprite(void){ return sprite; }
		PLATFORMENGINE_API color4 GetColor(void) { return color; }

		PLATFORMENGINE_API void GetPosition(float &x, float &y);
		PLATFORMENGINE_API void GetSize(float &x, float &y);


		PLATFORMENGINE_API virtual void SetAlpha(float alpha);
		PLATFORMENGINE_API virtual void SetAlphaSmooth(float alpha, float time);
		PLATFORMENGINE_API virtual void SetScaleSmooth(float scale, float time);
		PLATFORMENGINE_API virtual void Move(float px, float py, float time);

		virtual void Show(void);
		virtual void Hide(void);

		virtual void Create(CGuiManager *GUI, GuiElementSettings ges);
	};

	class CButton :public CGuiElement
	{
	public:

	};

	class CImage :public CGuiElement
	{

	};

	class CBox :public CGuiElement
	{
	private:
		std::vector<CGuiElement*> elementList;

	public:
		PLATFORMENGINE_API void AttachElement(CGuiElement *Element);
		PLATFORMENGINE_API void AttachElement(std::string name);
		PLATFORMENGINE_API void DeattachElement(CGuiElement *Element);

		PLATFORMENGINE_API void SetAlpha(float alpha);
		PLATFORMENGINE_API void SetAlphaSmooth(float alpha, float time);
		PLATFORMENGINE_API void SetScaleSmooth(float scale, float time);
		PLATFORMENGINE_API void Move(float px, float py, float time);

		void Show(void);
		void Hide(void);
	};

	class CText :public CGuiElement
	{
	private:
		int fontsize;
		int fontdepth;

		PE::CFont *font;
		wchar_t *text;

		TextAlign align;

		void Render(void);

	public:
		PLATFORMENGINE_API CText();
		PLATFORMENGINE_API ~CText();

		PLATFORMENGINE_API	void SetText(char *text);
		PLATFORMENGINE_API	void SetText(wchar_t *text);
		PLATFORMENGINE_API	void SetFontsize(int size);

		void Create(CGuiManager *GUI, TextSettings ts);
	};
};

#endif //_GUI_H_