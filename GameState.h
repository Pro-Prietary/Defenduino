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
#include "EnemyShot.h"
#include "Bomber.h"
#include "Mine.h"

#include <Arduboy2.h>

#define TOTAL_PLAYER_SHOTS 4
#define TOTAL_LANDERS 20
#define TOTAL_HUMANOIDS 10
#define TOTAL_PARTICLES 4
#define TOTAL_ENEMY_SHOTS 4
#define TOTAL_BOMBERS 5
#define TOTAL_MINES 6

#define NO_HUMANOID_FOUND 255

class GameState : public State
{
public:
	GameState();
	virtual void update();
	PlayerShot* getPlayerShot();
	EnemyShot* getEnemyShot();
	Mine* getMine();

	Particles* getParticles();
	void lostLife();
	GameCamera* getCamera();
	void freezeActors();
	void completeSpawningLander(int xPos, int yPos);
	uint8_t getCapturableHumanoidAtPosition(uint16_t xPos);
	Humanoid* getHumanoid(uint8_t index);
	void onCountedEnemyDeath();
	void addToScore(uint16_t toAdd);
	void onSmartBomb();

private:
	GameCamera camera;
	PlayerShip playerShip;
	PlayerShot playerShots[TOTAL_PLAYER_SHOTS];
	Lander landers[TOTAL_LANDERS];
	Landscape landscape;
	Humanoid humanoids[TOTAL_HUMANOIDS];
	Particles particles[TOTAL_PARTICLES];
	EnemyShot enemyShots[TOTAL_ENEMY_SHOTS];
	Bomber bombers[TOTAL_BOMBERS];
	Mine mines[TOTAL_MINES];

	unsigned long score = 0;
	unsigned long nextBonus = 10000;


	void startSpawningLander();
	bool spawnPosTooCloseToPlayer(int xPos);
	int getSafeSpawn();
	void spawnWave(uint8_t maxForLevel);
	void drawGui();
	void drawScanner();
	void plotOnScanner(uint8_t scannerY, GameObject* pGameObject);
	void inPlayUpdate();
	void interstitialUpdate();
	uint8_t getExpectedLandersForLevel();
	void onNewLevel();
	void onNewLife();
	void distributeActiveBombers();

	uint8_t flags = 0;
	uint8_t spawnedLanders = 0;
	uint8_t lives = 3;
	uint8_t smartBombs = 3;
	uint8_t remainingHumanoids = TOTAL_HUMANOIDS;
	uint8_t level = 0;
	uint8_t liveEnemies = 0;
	uint8_t smartbombCountdown = 0;

	uint16_t spawnCountdown = 0;

};

