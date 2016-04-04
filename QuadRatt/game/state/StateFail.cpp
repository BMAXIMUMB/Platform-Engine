// StateFail.cpp

#include "../game.h"
#include "../gamegui.h"
#include "StateFail.h"

CStateFail::CStateFail(CGameState *state)
{
	this->state = state;
}

void CStateFail::Update()
{

}

void CStateFail::LoopFunction()
{
	state->GetGame()->GetLevel()->Update();
	state->GetGame()->DebugInfoUpdate();
}

void CStateFail::GuiActionStop(Gui::CGuiElement *elem, int actionType)
{

}