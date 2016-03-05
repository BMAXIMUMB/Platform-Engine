// gamestate.cpp

#include "gamestate.h"
#include "game.h"

CGameState::CGameState(CGame* game)
{
	this->game = game;
	currentState = GAME_STATE_LOADING_IMAGE;
}

enGameState CGameState::Get()
{
	return currentState;
}

void CGameState::Set(enGameState state)
{
	enGameState tempGs = currentState;
	currentState = state;
	game->onGameStateChange(state, tempGs);
}