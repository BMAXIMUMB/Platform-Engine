// gui_manager.h

#ifndef _GUI_MANAGER_H_
#define _GUI_MANAGER_H_
#include "gui.h"
#include <vector>

#define GUI_ACTION_TYPE_MOVE			(0x1)
#define GUI_ACTION_TYPE_SCALE			(0x2)
#define GUI_ACTION_TYPE_ALPHA			(0x3)

#define POINT_IN_SQUARE(x1, x2, y1, y2, px, py) px >= x1 && px <= x2 && py >= y1 && py <= y2
#define GetElement FindElement

namespace Gui
{
	typedef void(*_OnActionStop)(CGuiElement*, int);

	class CGuiManager
	{
		friend class CGuiElement;
		friend class CText;
	private:
		std::vector<CGuiElement*> elementList;
		PE::CApplication *app;
		CGuiElement *clickedElement;

		void ElementAddToList(CGuiElement*);
		bool ElementDeleteToList(CGuiElement*);
		
		_OnElementClick _OnElementClick;
		_OnElementRelease _OnElementRelease;
		_OnActionStop _OnActionStop;

	public:
		PLATFORMENGINE_API CGuiManager(PE::CApplication *App);
		PLATFORMENGINE_API ~CGuiManager();

		PLATFORMENGINE_API CButton* CreateButton(GuiElementSettings ges);
		PLATFORMENGINE_API bool DestroyButton(CButton*);
		PLATFORMENGINE_API bool DestroyButton(std::string name);

		PLATFORMENGINE_API CImage* CreateImage(GuiElementSettings ges);
		PLATFORMENGINE_API bool DestroyImage(CImage*);
		PLATFORMENGINE_API bool DestroyImage(std::string name);

		PLATFORMENGINE_API CBox* CreateBox(GuiElementSettings ges);
		PLATFORMENGINE_API bool DestroyBox(CBox*);
		PLATFORMENGINE_API bool DestroyBox(std::string name);

		PLATFORMENGINE_API CText* CreateText(TextSettings ts);
		PLATFORMENGINE_API bool DestroyText(CText*);
		PLATFORMENGINE_API bool DestroyText(std::string name);

		PLATFORMENGINE_API void DrawElements(void);
		PLATFORMENGINE_API CGuiElement* FindElement(std::string name);
		PLATFORMENGINE_API CBox* GetBox(std::string name){ return (CBox*)FindElement(name); }
		PLATFORMENGINE_API CText* GetText(std::string name){ return (CText*)FindElement(name); }
		PLATFORMENGINE_API void Show(std::string name);
		PLATFORMENGINE_API void Hide(std::string name);

		void CheckElementCick(int button, int mposx, int mposy);
		void CheckElementRelease(int button, int mposx, int mposy);
		void UpdateMoving(int index, float dt);
		void UpdateAlpha(int index, float dt);
		void UpdateScaling(int index, float dt);
		void Update(float dt);

		PLATFORMENGINE_API void SetElementClickCallback(::_OnElementClick);
		PLATFORMENGINE_API void SetElementReleaseCallback(::_OnElementRelease);
		PLATFORMENGINE_API void SetActionStopCallback(Gui::_OnActionStop);

		PE::CApplication* GetApp(void){ return app; }

		// CALLBACKS
		void OnElementClick(int button, CGuiElement* Element);
		void OnElementRelease(CGuiElement* Element);
		void OnActionStop(CGuiElement *Element, int actiontype);
	};
};

#endif //_GUI_MANAGER_H_