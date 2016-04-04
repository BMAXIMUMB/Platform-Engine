// StateStarting.cpp

#include "../game.h"
#include "../gamegui.h"
#include "StateStarting.h"

CStateStarting::CStateStarting(CGameState *state)
{
	this->state = state;
}

void CStateStarting::Update()
{

}

void CStateStarting::LoopFunction()
{
	state->GetGame()->GetLevel()->Update();
	state->GetGame()->DebugInfoUpdate();
}

void CStateStarting::GuiActionStop(Gui::CGuiElement *elem, int actionType)
{
	if(elem->GetName() == "mm_box")
	{
		state->GetGame()->GetApp()->GUI->Hide("mm_box");
		state->GetGame()->GetStateID()->DispatchEvent(ON_MENU_HIDED);
	}
}