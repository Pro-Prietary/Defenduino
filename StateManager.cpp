#include <Arduboy2.h>
#include "StateManager.h"

StateManager::StateManager()
{
  
}

void StateManager::update()
{
  pCurrentState->update();

  // Time to move to a new state?
  if(pNextState!=NULL)
  {
    if(pCurrentState!=NULL)
    {
      delete(pCurrentState);
    }
    pCurrentState = pNextState;
    pNextState = NULL;
  }
}

void StateManager::setState(State* state)
{
  pNextState = state;
}


