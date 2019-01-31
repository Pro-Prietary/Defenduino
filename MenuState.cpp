#include "MenuState.h"
#include "StateManager.h"
#include "GameState.h"
#include "Globals.h"


MenuState::MenuState() : State(&camera)
{
	pressStartObj.setText(F("Press A To Start"));
	addObject(&pressStartObj);
}

void MenuState::update() 
{
	State::update();

	if (arduboy.justPressed(A_BUTTON)) 
	{
		stateManager.setState(&gameState);
	}
}