#include "MenuState.h"
#include "StateManager.h"
#include "GameState.h"
#include "Globals.h"


MenuState::MenuState() : State(&camera)
{
	pressStartObj.worldPos.x = 14;
	pressStartObj.worldPos.y = 10;

	pressStartObj.setText(F("Press A To Start"));
		
#ifdef _DEBUG
	debugMsg.setText(F("Debug Build"));
	debugMsg.worldPos.x = 25;
	debugMsg.worldPos.y = 40;
#endif

}

void MenuState::update() 
{
	if (arduboy.justPressed(A_BUTTON)) 
	{
		stateManager.setState(new GameState());
	}
	camera.render(&pressStartObj);
#ifdef _DEBUG
	camera.render(&debugMsg);
#endif
}
