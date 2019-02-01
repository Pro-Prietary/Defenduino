#pragma once

#include "State.h"
#include "TextObject.h"
#include "PlayerShip.h"
#include <Arduboy2.h>

class GameState : public State
{
public:
	GameState();


private:
	Camera camera;
	TextObject testText;
	PlayerShip playerShip;
};

