// StateGame.cpp

#include "../game.h"
#include "../gamegui.h"
#include "StateGame.h"

CStateGame::CStateGame(CGameState *state)
{
	this->state = state;
}

void CStateGame::Activate()
{

}

void CStateGame::Deactivate()
{

}

void CStateGame::Update()
{

}

void CStateGame::LoopFunction()
{
	state->GetGame()->GetLevel()->GetPlayer()->UpdateScore();
	state->GetGame()->GetInterface()->UpdatePlayerScore();

	state->GetGame()->GetLevel()->LoopFunction();
	state->GetGame()->GetLevel()->Check();
	state->GetGame()->DebugInfoUpdate();
}

void CStateGame::GuiActionStop(Gui::CGuiElement *elem, int actionType)
{
	if(elem->GetName() == "white_quad")
	{
		if(actionType == GUI_ACTION_TYPE_ALPHA)
		{
			state->GetGame()->GetApp()->GUI->Hide("white_quad");
		}
	}
}