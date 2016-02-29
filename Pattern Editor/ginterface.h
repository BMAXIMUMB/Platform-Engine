// ginterface.h

#ifndef _GINTERFACE_H_
#define _GINTERFACE_H_

#include "main.h"

class CGInterface
{
private:
	PE::CApplication *app;

	void CreateBottomPanel(void);

public:
	CGInterface(PE::CApplication *app);

	void Create(void);


	////////////////////////////////////////
	void OnActionStop(Gui::CGuiElement *elem, int actiontype);
	void OnElementClick(Gui::CGuiElement*, int);
	void OnElementRelease(Gui::CGuiElement*);
};

void __OnActionStop(Gui::CGuiElement*, int);
void __OnElementClick(int, Gui::CGuiElement*);
void __OnElementRelease(Gui::CGuiElement*);

void MouseDown(int, int, int);
void MouseUp(int, int, int);
void MouseMove(int, int);

#endif //_GINTERFACE_H_