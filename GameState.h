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

#define TOTAL_PLAYER_SHOTS 4
#define TOTAL_LANDERS 8
#define TOTAL_LANDSCAPE_SEGMENTS 8
#define TOTAL_HUMANOIDS 10

class GameState : public State
{
public:
	GameState();
	virtual void update();
	PlayerShot* getPlayerShot();

private:
	GameCamera camera;
	PlayerShip playerShip;
	PlayerShot playerShots[TOTAL_PLAYER_SHOTS];
	Lander landers[TOTAL_LANDERS];
	LandscapeSegment landscapeSegments[TOTAL_LANDSCAPE_SEGMENTS];
	Humanoid humanoids[TOTAL_HUMANOIDS];

	void spawnLander(int worldX);
};

