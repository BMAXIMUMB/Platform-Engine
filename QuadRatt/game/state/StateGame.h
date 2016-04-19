// StateGame.h

#pragma once

#include "state.h"

class CStateGame :public IState
{
public:
	CStateGame(CGameState *state);

	void Activate(void);
	void Deactivate(void);

	void Update(void);
	void LoopFunction(void);
	void GuiActionStop(Gui::CGuiElement *elem, int actionType);
};