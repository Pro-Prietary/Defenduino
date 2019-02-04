#pragma once

#include "State.h"
#include "TextObject.h"
#include <Arduboy2.h>

class MenuState : public State
{
public:
	MenuState();
	virtual void update();

private:
	Camera camera;
	TextObject pressStartObj;
	TextObject debugMsg;
};

