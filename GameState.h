#pragma once

#include "State.h"
#include "TextObject.h"
#include "PlayerShip.h"
#include "GameCamera.h"
#include "LandscapeSegment.h"
#include "Humanoid.h"
#include "PlayerShot.h"
#include "ObjectPool.h"
#include <Arduboy2.h>

class GameState : public State
{
public:
	GameState();
	PlayerShip* getPlayerShip();
	void pool(PlayerShot* laser);
	PlayerShot* getPlayerShot();

private:
	GameCamera camera;
	TextObject testText;
	PlayerShip playerShip;
	LandscapeSegment landscape[8];
	Humanoid humanoids[10];
	PlayerShot lasers[4];
	ObjectPool laserPool;

};

