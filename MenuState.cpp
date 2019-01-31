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
	arduboy.println("MenuState::update");
	if (arduboy.justPressed(A_BUTTON)) 
	{
		arduboy.println("Pressed");
		stateManager.setState(&gameState);
	}
}