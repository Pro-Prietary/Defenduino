#include <Arduboy2.h>
#include "StateManager.h"

StateManager::StateManager()
{
  
}

void StateManager::update()
{
  pCurrentState->update();
}


