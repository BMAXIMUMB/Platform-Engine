// gamestate.h

#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <vector>
#include "state/state.h"

#include "state/StateFail.h"
#include "state/StateGame.h"
#include "state/StateLoadingImage.h"
#include "state/StateLoadingResources.h"
#include "state/StateMainMenu.h"
#include "state/StateStarting.h"

//----------------------------------------------------------------------------------------------------------

class CGame;

enum Event
{
	ON_LOADING_IMAGE_SHOWED,
	ON_RESOURCES_LOADED,
	ON_PLAY_CLICKED,
	ON_MENU_HIDED,
	ON_PLAYER_FAIL,
	ON_RETRY
};

struct STransition
{
	IState *currentState;
	IState *targetState;
	Event currentEvent;
};

class CGameState
{
private:
	CGame *game;
	IState *currentState;
	std::vector<STransition> transitionsTable;

	void SetState(IState *state);

public:
	CGameState(CGame *game);
	~CGameState();

	IState* GetState(void);
	CGame *GetGame(void);

	void AddTransition(IState *fromState, Event _event, IState *toState);
	void DispatchEvent(Event currentEvent);

	CStateLoadingImage *StateLoadingImage;
	CStateLoadingResources *StateLoadingResources;
	CStateMainMenu *StateMainMenu;
	CStateGame *StateGame;
	CStateStarting *StateStarting;
	CStateFail *StateFail;

};

#endif //_GAMESTATE_H_