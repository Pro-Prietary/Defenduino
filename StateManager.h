#pragma once
#include "State.h"

class StateManager
{
public:
	StateManager();
	void setState(State* pNewState);
	void update();

private:
   State* pCurrentState;
   State* pNextState;
};

