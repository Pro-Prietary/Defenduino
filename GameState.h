#pragma once

#include "State.h"
#include "TextObject.h"
#include "PlayerShip.h"
#include "GameCamera.h"
#include "LandscapeSegment.h"
#include <Arduboy2.h>

class GameState : public State
{
public:
	GameState();
	PlayerShip* getPlayerShip();

private:
	GameCamera camera;
	TextObject testText;
	PlayerShip playerShip;
	LandscapeSegment landscape[8];
};

