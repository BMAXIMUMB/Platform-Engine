// StateFail.cpp

#include "../game.h"
#include "../gamegui.h"
#include "StateFail.h"

CStateFail::CStateFail(CGameState *state)
{
	this->state = state;
}

void CStateFail::Activate()
{
	state->GetGame()->PlayerFail();
}

void CStateFail::Deactivate()
{

}

void CStateFail::Update()
{

}

void CStateFail::LoopFunction()
{
	state->GetGame()->GetLevel()->LoopFunction();
	state->GetGame()->DebugInfoUpdate();
}

void CStateFail::GuiActionStop(Gui::CGuiElement *elem, int actionType)
{
	if(elem->GetName() == "white_quad")
	{
		if(actionType == GUI_ACTION_TYPE_ALPHA)
		{
			state->GetGame()->GetLevel()->Restart();
			state->GetGame()->GetStateID()->DispatchEvent(ON_RETRY);
			state->GetGame()->GetInterface()->ShowGameHUD();
			state->GetGame()->GetInterface()->HideWhiteScreen();
		}
	}
}