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
#include "Flaggable.h"
#include "EnemyShot.h"

#include <Arduboy2.h>

#define TOTAL_PLAYER_SHOTS 4
#define TOTAL_LANDERS 20
#define TOTAL_HUMANOIDS 10
#define TOTAL_PARTICLES 4
#define TOTAL_ENEMY_SHOTS 4

#define NO_HUMANOID_FOUND 255

class GameState : public State, public Flaggable
{
public:
	GameState();
	virtual void update();
	PlayerShot* getPlayerShot();
	EnemyShot* getEnemyShot();

	Particles* getParticles();
	void lostLife();
	GameCamera* getCamera();
	void freezeActors();
	void completeSpawningLander(int xPos, int yPos);
	uint8_t getCapturableHumanoidAtPosition(uint16_t xPos);
	Humanoid* getHumanoid(uint8_t index);
	uint8_t liveEnemiesRemaining = 0;
	unsigned long score = 0;


private:
	GameCamera camera;
	PlayerShip playerShip;
	PlayerShot playerShots[TOTAL_PLAYER_SHOTS];
	Lander landers[TOTAL_LANDERS];
	Landscape landscape;
	Humanoid humanoids[TOTAL_HUMANOIDS];
	Particles particles[TOTAL_PARTICLES];
	EnemyShot enemyShots[TOTAL_ENEMY_SHOTS];

	void startSpawningLander();
	bool spawnPosTooCloseToPlayer(int xPos);
	int getSafeLanderSpawn();
	void spawnWave(uint8_t maxForLevel);
	void drawGui();
	void drawScanner();
	void plotOnScanner(int scannerY, GameObject* pGameObject);

	uint8_t spawnedLanders = 0;
	uint8_t lives = 3;
	uint8_t smartBombs = 3;
	uint8_t remainingHumanoids = 10;
	uint8_t level = 1;

	uint8_t flags = 0;

	uint16_t spawnCountdown = 0;

};

