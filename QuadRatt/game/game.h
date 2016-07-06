// game.h

#ifndef _GAME_H_
#define _GAME_H_

#include <stack>
#include "../main.h"
#include "../debug.h"
#include "level.h"
#include "gamestate.h"

//----------------------------------------------------------------------------------------------------------

// Состояния игры

class CInterface;

class CGame
{
private:

	CLevel *level;
	CInterface *gInterface;
	CGameState *state;

	PE::CWorld *world;
	PE::CApplication	*app;

	//debug
	CDebug *debugInfo;

public:
	CGame(PE::CApplication *App);
	~CGame();

	PE::CApplication* GetApp(void){ return app; }
	PE::CWorld* GetWorld(void){ return world; }

	CInterface* GetInterface(void){ return gInterface; }
	CLevel* GetLevel(void){ return level; }
	CGameState* GetStateID(void) { return state; }

	void ShowDebugInfo(void);
	void DebugInfoUpdate(void);


	void Start();
	void Restart();

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
	void onGameStateChange(IState *newState, IState *oldState);
};

#endif /*_GAME_H_*/