#include "State.h"

class StateManager
{
private:
   StateManager();
   State* pCurrentState;
   State* pNextState;

public:
  void setState(State* pNewState);
   
static StateManager& instance()
{
  static StateManager INSTANCE;
  return INSTANCE;
}

   void update();
};

