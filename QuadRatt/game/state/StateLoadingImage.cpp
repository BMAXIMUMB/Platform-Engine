// StateLoadingImage.cpp

#include "../game.h"
#include "../gamegui.h"
#include "StateLoadingImage.h"

CStateLoadingImage::CStateLoadingImage(CGameState *state)
{
	this->state = state;
}

void CStateLoadingImage::Activate()
{

}

void CStateLoadingImage::Deactivate()
{

}

void CStateLoadingImage::Update()
{

}

void CStateLoadingImage::LoopFunction()
{

}

void CStateLoadingImage::GuiActionStop(Gui::CGuiElement *elem, int actionType)
{
	if(elem->GetName() == "img_loading")
	{
		if(actionType == GUI_ACTION_TYPE_ALPHA)
		{
			state->GetGame()->GetInterface()->onLoadingImageShowed();
		}
	}
}