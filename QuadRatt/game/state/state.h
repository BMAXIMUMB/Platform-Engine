// state.h

#pragma once

#include "../../main.h"

class CGameState;

class IState
{
protected:
	CGameState *state;

public:

	virtual void Activate(void);
	virtual void Deactivate(void);

	virtual void Update(void) = 0;
	virtual void LoopFunction(void) = 0;
	virtual void GuiActionStop(Gui::CGuiElement *elem, int actionType) = 0;

};