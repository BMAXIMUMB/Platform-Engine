// gamestate.h

#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

enum enGameState
{
	GAME_STATE_NO,
	GAME_STATE_LOADING_IMAGE,
	GAME_STATE_LOAD_RESOURCES,
	GAME_STATE_MAIN_MENU,
	GAME_STATE_GAME,
	GAME_STATE_STARTING,
	GAME_STATE_FAIL,
};

class CGame;
typedef void (CGame::* _SetState)(enGameState newstate, enGameState oldstate);

class CGameState
{

private:
	enGameState currentState;
	CGame *game;

public:
	CGameState(CGame*);

	enGameState Get(void);
	void Set(enGameState state);
};

#endif //_GAMESTATE_H_