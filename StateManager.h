#include "State.h"

class StateManager
{
private:
   StateManager();
   State* pCurrentState;

public:
   
static StateManager& instance()
{
  static StateManager INSTANCE;
  return INSTANCE;
}

   void update();
};

