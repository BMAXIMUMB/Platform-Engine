// StateStarting.h

#pragma once

#include "state.h"

class CStateStarting :public IState
{
public:
	CStateStarting(CGameState *state);

	void Activate(void);
	void Deactivate(void);

	void Update(void);
	void LoopFunction(void);
	void GuiActionStop(Gui::CGuiElement *elem, int actionType);
};