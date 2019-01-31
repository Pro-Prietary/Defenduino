#include "GameState.h"
#include "StateManager.h"

GameState::GameState() : State(&camera)
{
	testText.setText(F("Game State"));
	addObject(&testText);
}