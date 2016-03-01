// gameguigui.cpp (QuadRatt)

// Тут хуёвая реализация архитектуры
// Нужно переделать, а то сам нихуя не понимаю

#include "gamegui.h"
#include "game.h"
#include "../program.h"

extern CProgram *gProgram;

CInterface::CInterface(CGame *Game)
{
	this->game = Game;
	this->app = Game->GetApp();

	app->GUI->SetActionStopCallback(__OnActionStop);
	app->GUI->SetElementClickCallback(__OnElementClick);
	app->GUI->SetElementReleaseCallback(__OnElementRelease);
}

CInterface::~CInterface()
{

}

void CInterface::CreateGUIMainMenu()
{
	GuiElementSettings ges;

	//background
	ges.posX = 640;
	ges.posY = 360;
	ges.sizeX = 1280;
	ges.sizeY = 720;
	ges.sprite = app->spriteManager->Get("mm_background");
	ges.name = "mm_box";
	ges.color = {1, 1, 1, 0.5};
	app->GUI->CreateBox(ges);

	//logo
	ges.posX = 640;
	ges.posY = 600;
	ges.sizeX = 650;
	ges.sizeY = 180;
	ges.sprite = app->spriteManager->Get("mm_logo");
	ges.name = "mm_logo";
	ges.color = {1, 1, 1, 0.5};
	app->GUI->CreateImage(ges);

	// button "play"
	ges.posX = 640;
	ges.posY = 360;
	ges.sizeX = 175;
	ges.sizeY = 235;
	ges.sprite = app->spriteManager->Get("mm_button_play");
	ges.name = "mm_button_play";
	ges.color = {1, 1, 1, 0.5};
	app->GUI->CreateButton(ges);

	app->GUI->GetBox("mm_box")->AttachElement("mm_button_play");
	app->GUI->GetBox("mm_box")->AttachElement("mm_logo");
}

void CInterface::CreateGameHUD()
{
	TextSettings ts;
	ts.color = {0.0, 0.0, 0.0, 1.0};
	ts.font = app->fontManager->Get("Arial2");
	ts.fontsize = 35;
	ts.name = "player_score";
	ts.posX = 640;
	ts.posY = 680;
	ts.text = L"0";

	app->GUI->CreateText(ts);
}

void CInterface::CreateGUI(void)
{
	CreateGUIMainMenu();
	CreateGameHUD();
}

void CInterface::ShowGameHUD()
{
	app->GUI->Show("player_score");
}

void CInterface::ShowMainMenu(gamestate oldgs)
{
	if(oldgs == GAME_STATE_LOAD_RESOURCES)
	{
		HideLoadingImage();
	}
}

void CInterface::HideMainMenu()
{
	app->GUI->GetElement("mm_box")->SetAlphaSmooth(0.0, 0.5);
}

void CInterface::ShowLoadingImage(void)
{
	GuiElementSettings ges;

	ges.posX = 640;
	ges.posY = 360;
	ges.sizeX = 1280;
	ges.sizeY = 720;
	ges.sprite = app->spriteManager->Load("resources\\sprites\\loading.sprite", "s_loading");
	ges.name = "img_loading";
	ges.color = {1, 1, 1, 0.0};
	app->GUI->CreateImage(ges);
	app->GUI->Show("img_loading");
	app->GUI->GetElement("img_loading")->SetAlphaSmooth(1.0, 3.0);
}

void CInterface::HideLoadingImage()
{
	app->GUI->GetElement("img_loading")->SetAlphaSmooth(0.0f, 1.1);
}

void CInterface::UpdatePlayerScore()
{
	char str[12];

	sprintf(str, "%d/%d", game->GetLevel()->GetPlayer()->GetScore(), game->GetLevel()->GetPlayer()->GetBestScore());
	app->GUI->GetText("player_score")->SetText(str);
}


//CALLBACKS
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////

void CInterface::onLoadingImageShowed()
{
	game->SetState(GAME_STATE_LOAD_RESOURCES);
}

void CInterface::onLoadingImageHided()
{
	app->GUI->Hide("img_loading");

	app->GUI->GetElement("mm_box")->SetAlpha(0.0);
	app->GUI->GetElement("mm_box")->SetAlphaSmooth(0.5, 0.5);
	app->GUI->Show("mm_box");
}

void CInterface::onActionStop(Gui::CGuiElement *elem, int actiontype)
{
	if(elem->GetName() == "img_loading")
	{
		if(actiontype == GUI_ACTION_TYPE_ALPHA)
		{
			if(game->GetState() == GAME_STATE_LOADING_IMAGE)
			{
				onLoadingImageShowed();
			}
			else if(game->GetState() == GAME_STATE_MAIN_MENU)
			{
				onLoadingImageHided();
			}
		}
	}
	else if(elem->GetName() == "mm_box")
	{
		if(game->GetState() == GAME_STATE_STARTING)
		{
			app->GUI->Hide("mm_box");
			game->SetState(GAME_STATE_GAME);
		}
	}
}

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////

void CInterface::onElementClick(Gui::CGuiElement *elem, int button)
{
	if(elem->GetName() == "mm_button_play" && button == PE_MOUSE_LBUTTON)
	{
		game->SetState(GAME_STATE_STARTING);
	}
}

void CInterface::onElementRelease(Gui::CGuiElement *elem)
{

}

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////

// Костыли. А как иначе?
void __OnActionStop(Gui::CGuiElement *elem, int actiontype)
{
	gProgram->GetGame()->GetInterface()->onActionStop(elem, actiontype);
}

void __OnElementClick(int button, Gui::CGuiElement *elem)
{
	gProgram->GetGame()->GetInterface()->onElementClick(elem, button);
}

void __OnElementRelease(Gui::CGuiElement *elem)
{
	gProgram->GetGame()->GetInterface()->onElementRelease(elem);
}