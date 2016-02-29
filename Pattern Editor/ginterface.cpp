// ginterface.cpp

#include "ginterface.h"
#include "program.h"

extern CProgram *gProgram;

CGInterface::CGInterface(PE::CApplication *app)
{
	this->app = app;

	app->GUI->SetActionStopCallback(__OnActionStop);
	app->GUI->SetElementClickCallback(__OnElementClick);
	app->GUI->SetElementReleaseCallback(__OnElementRelease);
}

///////////////////////////////////////////////////////////////////////

void CGInterface::CreateBottomPanel()
{
	GuiElementSettings ges;

	ges.posX = 100;
	ges.posY = 100;
	ges.sizeX = 100;
	ges.sizeY = 100;
	ges.name = "mainBox";
	app->GUI->CreateBox(ges);

	app->GUI->Show("mainBox");
}

void CGInterface::Create()
{
	CreateBottomPanel();
}

void CGInterface::OnActionStop(Gui::CGuiElement *elem, int actiontyp)
{

}

void CGInterface::OnElementClick(Gui::CGuiElement *elem, int button)
{

}

void CGInterface::OnElementRelease(Gui::CGuiElement *elem)
{

}


////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////


void __OnActionStop(Gui::CGuiElement *elem, int actiontype)
{
	gProgram->GetGui()->OnActionStop(elem, actiontype);
}

void __OnElementClick(int button, Gui::CGuiElement *elem)
{
	gProgram->GetGui()->OnElementClick(elem, button);
}

void __OnElementRelease(Gui::CGuiElement *elem)
{
	gProgram->GetGui()->OnElementRelease(elem);
}