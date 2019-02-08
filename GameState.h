#pragma once

#include "State.h"
#include "TextObject.h"
#include "PlayerShip.h"
#include "GameCamera.h"
#include "LandscapeSegment.h"
#include "Humanoid.h"
#include "PlayerShot.h"
#include "ObjectPool.h"
#include "Lander.h"

#include <Arduboy2.h>

class GameState : public State
{
public:
	GameState();
	PlayerShip* getPlayerShip();
	void pool(PlayerShot* laser, GameObject* pPrevSibling);
	PlayerShot* getPlayerShot();

private:
	GameCamera camera;
	TextObject testText;
	PlayerShip playerShip;
	LandscapeSegment landscape[8];
	Humanoid humanoids[10];
	PlayerShot lasers[4];
	Lander landers[8];
	ObjectPool laserPool;
	ObjectPool landerPool;

	void spawnLander(int worldX);
};

