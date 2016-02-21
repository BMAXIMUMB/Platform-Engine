// game.h

#ifndef _GAME_H_
#define _GAME_H_

#include "../main.h"
#include "level.h"
#include "../debug.h"

#include <stack>

// Состояния игры
enum gamestate
{
	GAME_STATE_NO,
	GAME_STATE_LOADING_IMAGE,
	GAME_STATE_LOAD_RESOURCES,
	GAME_STATE_MAIN_MENU,
	GAME_STATE_GAME,
	GAME_STATE_STARTING,
};

class CInterface;

class CGame
{
private:

	std::stack<gamestate> state;

	CLevel *level;
	CInterface *gInterface;

	PE::CWorld *world;
	PE::CApplication	*app;

	//debug
	CDebug *debugInfo;

public:
	CGame(PE::CApplication *App);
	~CGame();

	PE::CApplication* GetApp(void){ return app; }

	CInterface* GetInterface(void){ return gInterface; }
	CLevel* GetLevel(void){ return level; }


	gamestate GetState(void);

	void SetState(gamestate _gamestate);
	void DownState(void);
	void ShowDebugInfo(void);
	void DebugInfoUpdate(void);


	void Start();

	void PlayerFail(void);

	//
	void LoadFonts(void);
	void LoadSprites(void);
	void LoadResources(void);

	// CALLBACKS
	void LoopFunction(void);
	void onObjectCollision(PE::CContact *Contact);
	void onKeyDown(int);
	void onKeyUp(int);
	void onMouseDown(int, int, int);
	void onMouseUp(int, int, int);
	void onMouseMove(int, int);
	void onGameStateChange(gamestate newgs, gamestate oldgs);
};

#endif /*_GAME_H_*/