#include "GameState.h"
#include "StateManager.h"
#include "Globals.h"

GameState::GameState() : State(&camera)
{
	testText.setText(F("Game State"));
	addObject(&landscape);
	addObject(&playerShip);
}

PlayerShip* GameState::getPlayerShip()
{
	return &playerShip;
}
