#include <Arduboy2.h>
#include "StateManager.h"
#include "Globals.h"

StateManager::StateManager()
{
}

void StateManager::update()
{
	// Time to move to a new state?
	if (pNextState != NULL)
	{
		pCurrentState = pNextState;
		pNextState = NULL;
	}

	pCurrentState->update();
}

void StateManager::setState(State* state)
{
  pNextState = state;
}


