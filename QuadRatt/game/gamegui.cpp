// gameguigui.cpp 

// Тут хуёвая реализация архитектуры(или нет)
// Нужно переделать, а то сам нихуя не понимаю

#include "gamegui.h"
#include "game.h"
#include "../program.h"

//----------------------------------------------------------------------------------------------------------

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

void CInterface::CreateIcons()
{
	GuiElementSettings ges;

	// Размер иконок одинаковый для всех
	ges.sizeX = ICON_SIZE;
	ges.sizeY = ICON_SIZE;

	// icon stats
	ges.posX = 640;
	ges.posY = ICON_POS_Y;
	ges.sprite = app->spriteManager->Get("g_icon_stats");
	ges.name = "g_icon_stats";
	ges.color = {1, 1, 1, 1.0};
	app->GUI->CreateImage(ges);

	// icon star
	ges.posX = 512;
	ges.posY = ICON_POS_Y;
	ges.sprite = app->spriteManager->Get("g_icon_star");
	ges.name = "g_icon_star";
	ges.color = {1, 1, 1, 1.0};
	app->GUI->CreateImage(ges);

	// icon sound on
	ges.posX = 768;
	ges.posY = ICON_POS_Y;
	ges.sprite = app->spriteManager->Get("g_icon_sound_on");
	ges.name = "g_icon_sound_on";
	ges.color = {1, 1, 1, 1.0};
	app->GUI->CreateImage(ges);

	// icon sound off
	ges.posX = 768;
	ges.posY = ICON_POS_Y;
	ges.sprite = app->spriteManager->Get("g_icon_sound_off");
	ges.name = "g_icon_sound_off";
	ges.color = {1, 1, 1, 1.0};
	app->GUI->CreateImage(ges);

	// icon retry
	ges.posX = 768;
	ges.posY = ICON_POS_Y;
	ges.sprite = app->spriteManager->Get("g_icon_retry");
	ges.name = "g_icon_retry";
	ges.color = {1, 1, 1, 1.0};
	app->GUI->CreateImage(ges);

	// icon house
	ges.posX = 512;
	ges.posY = ICON_POS_Y;
	ges.sprite = app->spriteManager->Get("g_icon_house");
	ges.name = "g_icon_house";
	ges.color = {1, 1, 1, 1.0};
	app->GUI->CreateImage(ges);

	// icon star fail
	ges.posX = 640;
	ges.posY = ICON_POS_Y;
	ges.sprite = app->spriteManager->Get("g_icon_star");
	ges.name = "g_icon_starfail";
	ges.color = {1, 1, 1, 1.0};
	app->GUI->CreateImage(ges);

	// icon pause
	ges.posX = 1250;
	ges.posY = 690;
	ges.sizeX = 32;
	ges.sizeY = 32;
	ges.sprite = app->spriteManager->Get("g_icon_pause");
	ges.name = "g_icon_pause";
	ges.color = {1, 1, 1, 1.0};
	app->GUI->CreateImage(ges);
}

void CInterface::CreateGUIFailMenu()
{
	GuiElementSettings	ges;
	TextSettings		ts;

	// box
	ges.posX = 640;
	ges.posY = 360;
	ges.sizeX = 1280;
	ges.sizeY = 720;
	ges.name = "fail_box";
	ges.color = {1, 1, 1, 1.0};
	app->GUI->CreateBox(ges);

	// "game over"
	ges.posX = 640;
	ges.posY = 602;
	ges.sizeX = 602;
	ges.sizeY = 74;
	ges.sprite = app->spriteManager->Get("g_fail_logo");
	ges.name = "g_fail_logo";
	ges.color = {1, 1, 1, 1.0};
	app->GUI->CreateImage(ges);

	// current score
	ts.color = {1.0, 1.0, 1.0, 1.0};
	ts.font = app->fontManager->Get("Utsaah2");
	ts.fontsize = 72;
	ts.name = "cur_score";
	ts.posX = 640;
	ts.posY = 414;
	ts.text = L"0";
	ts.align = ALIGN_CENTER;
	app->GUI->CreateText(ts);

	// best score
	ts.color = {1.0, 1.0, 1.0, 1.0};
	ts.font = app->fontManager->Get("Utsaah3");
	ts.fontsize = 72;
	ts.name = "best_score";
	ts.posX = 640;
	ts.posY = 346;
	ts.text = L"0";
	ts.align = ALIGN_CENTER;
	app->GUI->CreateText(ts);

	// attach elemens
	app->GUI->GetBox("fail_box")->AttachElement("g_fail_logo");
	app->GUI->GetBox("fail_box")->AttachElement("g_icon_retry");
	app->GUI->GetBox("fail_box")->AttachElement("g_icon_house");
	app->GUI->GetBox("fail_box")->AttachElement("g_icon_starfail");
	app->GUI->GetBox("fail_box")->AttachElement("cur_score");
	app->GUI->GetBox("fail_box")->AttachElement("best_score");
}

void CInterface::CreateGUIMainMenu()
{
	GuiElementSettings ges;

	// box
	ges.posX = 640;
	ges.posY = 360;
	ges.sizeX = 1280;
	ges.sizeY = 720;
	ges.name = "mm_box";
	ges.color = {1, 1, 1, 1.0};
	app->GUI->CreateBox(ges);

	// logo
	ges.posX = 640;
	ges.posY = 602;
	ges.sizeX = 546;
	ges.sizeY = 78;
	ges.sprite = app->spriteManager->Get("g_mm_logo");
	ges.name = "g_mm_logo";
	ges.color = {1, 1, 1, 1.0};
	app->GUI->CreateImage(ges);

	// "tap to play"
	ges.posX = 640;
	ges.posY = 348;
	ges.sizeX = 234;
	ges.sizeY = 138;
	ges.sprite = app->spriteManager->Get("g_mm_play");
	ges.name = "g_mm_play";
	ges.color = {1, 1, 1, 1.0};
	app->GUI->CreateImage(ges);

	// attach elements
	app->GUI->GetBox("mm_box")->AttachElement("g_mm_logo");
	app->GUI->GetBox("mm_box")->AttachElement("g_mm_play");
	app->GUI->GetBox("mm_box")->AttachElement("g_icon_stats");
	app->GUI->GetBox("mm_box")->AttachElement("g_icon_star");
	app->GUI->GetBox("mm_box")->AttachElement("g_icon_sound_on");
}

void CInterface::CreateGameHUD()
{
	GuiElementSettings	ges;
	TextSettings		ts;

	ts.color = {1.0, 1.0, 1.0, 1.0};
	ts.font = app->fontManager->Get("Utsaah1");
	ts.fontsize = 50;
	ts.name = "player_score";
	ts.posX = 640;
	ts.posY = 680;
	ts.text = L"0";
	ts.align = ALIGN_CENTER;

	app->GUI->CreateText(ts);

	ges.posX = 640;
	ges.posY = 360;
	ges.sizeX = 1280;
	ges.sizeY = 720;
	ges.name = "white_quad";
	ges.sprite = app->spriteManager->Get("g_white");
	ges.color = {1, 1, 1, 1.0};
	app->GUI->CreateImage(ges);
}

void CInterface::CreateGUI()
{
	CreateIcons();
	CreateGUIMainMenu();
	CreateGUIFailMenu();
	CreateGameHUD();
}

/////////////////////////////////////////////////////////////////////////////

void CInterface::ShowGameHUD()
{
	app->GUI->Show("player_score");
	app->GUI->Show("g_icon_pause");
}

void CInterface::HideGameHUD()
{
	app->GUI->Hide("player_score");
	app->GUI->Hide("g_icon_pause");
}

/////////////////////////////////////////////////////////////////////////////

void CInterface::ShowMainMenu(IState *oldState)
{
	if(oldState == game->GetStateID()->StateLoadingResources)
	{
		HideLoadingImage();
	}
}

void CInterface::HideMainMenu()
{
	app->GUI->GetElement("mm_box")->SetAlphaSmooth(0.0, 0.5);
}

/////////////////////////////////////////////////////////////////////////////

void CInterface::ShowFailMenu()
{
	char str[32];

	sprintf(str, "SCORE   %d", game->GetLevel()->GetPlayer()->GetScore());
	app->GUI->GetText("cur_score")->SetText(str);

	sprintf(str, "BEST   %d", game->GetLevel()->GetPlayer()->GetBestScore());
	app->GUI->GetText("best_score")->SetText(str);


	app->GUI->Show("fail_box");
	app->GUI->GetElement("fail_box")->SetAlpha(0.0f);
	app->GUI->GetElement("fail_box")->SetAlphaSmooth(1.0f, 1.0f);
}

void CInterface::HideFailMenu()
{
	//ShowWhiteScreen();
	//app->GUI->GetElement("fail_box")->SetAlphaSmooth(0.0f, 0.5f);

	app->GUI->Hide("fail_box");
}

void CInterface::ShowWhiteScreen()
{
	app->GUI->GetElement("white_quad")->SetAlpha(0.0f);
	app->GUI->GetElement("white_quad")->SetAlphaSmooth(1.0f, 1.0f);
}

/////////////////////////////////////////////////////////////////////////////

void CInterface::ShowLoadingImage()
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
	app->GUI->GetElement("img_loading")->SetAlphaSmooth(0.0f, 1.1f);
}

/////////////////////////////////////////////////////////////////////////////

void CInterface::UpdatePlayerScore()
{
	char str[12];

	sprintf(str, "%d", game->GetLevel()->GetPlayer()->GetScore());
	app->GUI->GetText("player_score")->SetText(str);
}


//CALLBACKS
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////

void CInterface::onLoadingImageShowed()
{
	game->GetStateID()->DispatchEvent(ON_LOADING_IMAGE_SHOWED);
}

void CInterface::onLoadingImageHided()
{
	app->GUI->Hide("img_loading");

	app->GUI->GetElement("mm_box")->SetAlpha(0.0);
	app->GUI->GetElement("mm_box")->SetAlphaSmooth(1.0, 0.5);
	app->GUI->Show("mm_box");
}

void CInterface::onActionStop(Gui::CGuiElement *elem, int actiontype)
{
	game->GetStateID()->GetState()->GuiActionStop(elem, actiontype);
}

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////

void CInterface::onElementClick(Gui::CGuiElement *elem, int button)
{
	if(elem->GetName() == "mm_box" && button == PE_MOUSE_LBUTTON)
	{
		game->GetStateID()->DispatchEvent(ON_PLAY_CLICKED);
	}
	
	if(game->GetStateID()->GetState() == game->GetStateID()->StateFail)
	{
		if(elem->GetName() == "g_icon_retry")
		{
			game->GetLevel()->Restart();
			game->GetStateID()->DispatchEvent(ON_RETRY);
			ShowGameHUD();
		}
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