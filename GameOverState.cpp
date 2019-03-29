#include "GameOverState.h"
#include "Globals.h"

GameOverState::GameOverState()
{

}

void GameOverState::update()
{
	smallFont.setCursor(35, 10);
	smallFont.print(F("GAME OVER"));

	if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON))
	{
		setState(STATE_MENU);
	}
}