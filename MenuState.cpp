#include "MenuState.h"
#include "GameState.h"
#include "Globals.h"


MenuState::MenuState()
{
}

void MenuState::update() 
{
	if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON))
	{
		setState(STATE_GAME);
	}

	arduboy.setCursor(14, 10);
	arduboy.print(F("Press A To Start"));

#ifdef _DEBUG
	arduboy.setCursor(25, 40);
	arduboy.print(F("Debug Build"));
#endif
}
