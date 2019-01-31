#pragma once

#include "State.h"
#include "TextObject.h"
#include <Arduboy2.h>

class GameState : public State
{
public:
	GameState();
	virtual void update();

private:
	Camera camera;
	TextObject testText;
};

