// StateMainMenu.cpp

#include "../game.h"
#include "../gamegui.h"
#include "StateMainMenu.h"

CStateMainMenu::CStateMainMenu(CGameState *state)
{
	this->state = state;
}

void CStateMainMenu::Activate()
{

}

void CStateMainMenu::Deactivate()
{

}

void CStateMainMenu::Update()
{

}

void CStateMainMenu::LoopFunction()
{
	state->GetGame()->GetLevel()->LoopFunction();
	state->GetGame()->DebugInfoUpdate();
}

void CStateMainMenu::GuiActionStop(Gui::CGuiElement *elem, int actionType)
{
	if(elem->GetName() == "img_loading")
	{
		if(actionType == GUI_ACTION_TYPE_ALPHA)
		{
			state->GetGame()->GetInterface()->onLoadingImageHided();
		}
	}
}