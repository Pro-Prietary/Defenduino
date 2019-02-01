#pragma once

#include "State.h"
#include "TextObject.h"
#include "PlayerShip.h"
#include "GameCamera.h"
#include <Arduboy2.h>

class GameState : public State
{
public:
	GameState();

private:
	GameCamera camera;
	TextObject testText;
	PlayerShip playerShip;
};

