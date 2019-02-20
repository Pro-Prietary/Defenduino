#pragma once

#include "State.h"
#include "TextObject.h"
#include "PlayerShip.h"
#include "GameCamera.h"
#include "Humanoid.h"
#include "PlayerShot.h"
#include "Lander.h"
#include "Landscape.h"
#include "Particles.h"

#include <Arduboy2.h>

#define TOTAL_PLAYER_SHOTS 4
#define TOTAL_LANDERS 8
#define TOTAL_HUMANOIDS 10
#define TOTAL_PARTICLES 4

class GameState : public State
{
public:
	GameState();
	virtual void update();
	PlayerShot* getPlayerShot();
	Particles* getParticles();
	void lostLife();

private:
	GameCamera camera;
	PlayerShip playerShip;
	PlayerShot playerShots[TOTAL_PLAYER_SHOTS];
	Lander landers[TOTAL_LANDERS];
	Landscape landscape;
	Humanoid humanoids[TOTAL_HUMANOIDS];
	Particles particles[TOTAL_PARTICLES];

	void spawnLander(int worldX);

	byte enemies = 0;
	byte lives = 3;
	byte smartBombs = 3;
	byte remainingHumanoids = 10;

	int score = 0;
};

