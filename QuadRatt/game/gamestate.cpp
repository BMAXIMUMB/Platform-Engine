// gamestate.cpp

#include "gamestate.h"
#include "game.h"

//----------------------------------------------------------------------------------------------------------

CGameState::CGameState(CGame *game)
{
	this->game = game;

	StateLoadingImage			= new CStateLoadingImage(this);
	StateLoadingResources	= new CStateLoadingResources(this);
	StateMainMenu					= new CStateMainMenu(this);
	StateGame							= new CStateGame(this);
	StateStarting					= new CStateStarting(this);
	StateFail							= new CStateFail(this);

	// Задаём начальное состояние
	currentState = StateLoadingImage;

	// Настройка таблицы переходов
	AddTransition(StateLoadingImage, ON_LOADING_IMAGE_SHOWED, StateLoadingResources);
	AddTransition(StateLoadingResources, ON_RESOURCES_LOADED, StateMainMenu);
	AddTransition(StateMainMenu, ON_PLAY_CLICKED, StateStarting);
	AddTransition(StateStarting, ON_MENU_HIDED, StateGame);
	AddTransition(StateGame, ON_PLAYER_FAIL, StateFail);
	AddTransition(StateFail, ON_RETRY, StateGame);
}

CGameState::~CGameState()
{

}

void CGameState::SetState(IState *state)
{
	currentState->Deactivate();

	currentState = state;
	currentState->Activate();
}

IState* CGameState::GetState()
{
	return currentState;
}

CGame* CGameState::GetGame()
{
	return game;
}

void CGameState::AddTransition(IState *fromState, Event _event, IState *toState)
{
	STransition transition = { fromState, toState, _event };

	transitionsTable.push_back(transition);
}

void CGameState::DispatchEvent(Event currentEvent)
{
	for(unsigned int i = 0; i < transitionsTable.size(); i++)
	{
		if(transitionsTable[i].currentState == currentState && transitionsTable[i].currentEvent == currentEvent)
		{
			IState *tempState = currentState;

			#ifdef _DEBUG
				logprintf("set state");
			#endif

			SetState(transitionsTable[i].targetState);
			game->onGameStateChange(transitionsTable[i].targetState, tempState);
			return;
		}
	}
}