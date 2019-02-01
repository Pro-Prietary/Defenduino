#include "GameState.h"
#include "StateManager.h"
#include "Globals.h"

GameState::GameState() : State(&camera)
{
	testText.setText(F("Game State"));
	addObject(&playerShip);
}
