// gamegui.h(QuadRatt)

#ifndef _GAMEGUI_H_
#define _GAMEGUI_H_

#include "../main.h"
#include "../../Platform Engine/gui/gui.h"
#include "game.h"

class CInterface
{
private:
	CGame *game;
	gamestate gstate;

	PE::CApplication *app;

	void CreateGUIMainMenu(void);
	void CreateGameHUD(void);

public:

	CInterface(CGame *Game);
	~CInterface();

	void CreateGUI(void);

	// Start Loading Image
	void ShowLoadingImage(void);
	void HideLoadingImage(void);

	// Main Menu
	void ShowMainMenu(gamestate oldgs);
	void HideMainMenu(void);

	// Game HUDS
	void ShowGameHUD(void);
	
	void UpdatePlayerScore(void);

	//CALLBACKS
	void onLoadingImageShowed(void);
	void onLoadingImageHided(void);
	void onActionStop(Gui::CGuiElement *elem, int actiontype);
	void onElementClick(Gui::CGuiElement*, int);
	void onElementRelease(Gui::CGuiElement*);
};

void __OnActionStop(Gui::CGuiElement*, int);
void __OnElementClick(int, Gui::CGuiElement*);
void __OnElementRelease(Gui::CGuiElement*);

#endif //_GAMEGUI_H_