// StateLoadingResources.h

#pragma once

#include "state.h"

class CStateLoadingResources :public IState
{
public:
	CStateLoadingResources(CGameState *state);

	void Activate(void);
	void Deactivate(void);

	void Update(void);
	void LoopFunction(void);
	void GuiActionStop(Gui::CGuiElement *elem, int actionType);
};