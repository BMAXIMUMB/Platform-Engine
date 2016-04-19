// StateMainMenu.h

#pragma once

#include "state.h"

class CStateMainMenu :public IState
{
public:
	CStateMainMenu(CGameState *state);

	void Activate(void);
	void Deactivate(void);

	void Update(void);
	void LoopFunction(void);
	void GuiActionStop(Gui::CGuiElement *elem, int actionType);
};