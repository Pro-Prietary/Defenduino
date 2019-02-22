#include "GameOverState.h"
#include "Globals.h"

GameOverState::GameOverState()
{

}

void GameOverState::update()
{
	arduboy.setCursor(35, 10);
	arduboy.print(F("GAME OVER"));

	if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON))
	{
		stateManager.setState(new MenuState());
	}
}