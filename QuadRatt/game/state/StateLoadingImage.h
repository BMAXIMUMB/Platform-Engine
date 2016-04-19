// StateLoadingImage.h

#pragma once

#include "state.h"

class CStateLoadingImage :public IState
{
public:
	CStateLoadingImage(CGameState *state);

	void Activate(void);
	void Deactivate(void);

	void Update(void);
	void LoopFunction(void);
	void GuiActionStop(Gui::CGuiElement *elem, int actionType);
};