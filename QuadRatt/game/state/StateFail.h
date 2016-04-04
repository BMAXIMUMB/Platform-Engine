// StateFail.h

#pragma once

#include "state.h"

class CStateFail :public IState
{
public:
	CStateFail(CGameState *state);

	void Update(void);
	void LoopFunction(void);
	void GuiActionStop(Gui::CGuiElement *elem, int actionType);
};