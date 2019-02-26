#include "GameState.h"
#include "StateManager.h"
#include "Globals.h"
#include "GameOverState.h"

#define LANDER_SPAWN_ALT -20

#define FLAG_FREEZE_ACTORS 0x1

#define SPAWN_INTERVAL 600

GameState::GameState() : State()
{
	//arduboy.initRandomSeed();
	srand(arduboy.generateRandomSeed());
	playerShip.setActive(true);

	for (int i = 0; i < TOTAL_HUMANOIDS; i++)
	{
		float xVel;
		if (rand() % 2 == 0)
		{
			xVel = 5;
		}
		else
		{
			xVel = -5;
		}
		humanoids[i].velocity.x = xVel;
		humanoids[i].worldPos.x = rand() % 1024;
		humanoids[i].worldPos.y = 29;
		humanoids[i].setActive(true);

	}
}

GameCamera* GameState::getCamera()
{
	return &camera;
}


// Tries to start spawning a lander, but no guaranteed to do so if
// no resources are available.
void GameState::startSpawningLander()
{
	int worldX = getSafeLanderSpawn();

	Particles* pParticles = getParticles();

	if (pParticles != NULL)
	{
		pParticles->worldPos.x = worldX;
		pParticles->worldPos.y = LANDER_SPAWN_ALT;
		pParticles->show(PARTICLES_SPAWN);
	}
#ifdef _DEBUG
	else
	{
		Serial.println(F("Tried to spawn lander but no particles are available."));
	}
#endif
}

int GameState::getSafeLanderSpawn()
{
	int worldX = rand() % 1024;
	while (spawnPosTooCloseToPlayer(worldX))
	{
		worldX = rand() % 1024;
	}
	return worldX;
}

bool GameState::spawnPosTooCloseToPlayer(int xPos)
{
	return abs(xPos - playerShip.worldPos.x) < 64
		|| (playerShip.worldPos.x >= (1024 - 64) && abs(xPos - (playerShip.worldPos.x - 1024)) < 64)
		|| (playerShip.worldPos.x <= 64 && abs(xPos - (playerShip.worldPos.x + 1024)) < 64);

}

void GameState::update()
{
	bool freezeActors = isFlagSet(FLAG_FREEZE_ACTORS);

	uint8_t expectedLanders = level == 1 ? 15 : 20;
	if(!freezeActors && spawnedLanders < expectedLanders)
	{
		if (spawnCountdown == 0)
		{
			spawnWave(expectedLanders);
		}
		else
		{
			spawnCountdown--;
		}
	}

	if (playerShip.isActive())
	{
		playerShip.update();
		camera.update(&playerShip);
		playerShip.render(camera.worldToScreenPos(playerShip.worldPos));
	}

	landscape.render(camera.worldPos.x);

	for (int i = 0; i < TOTAL_PLAYER_SHOTS; i++)
	{
		if (playerShots[i].isActive())
		{
			if (!freezeActors)
			{
				playerShots[i].update();
			}
			playerShots[i].render(camera.worldToScreenPos(playerShots[i].worldPos));
		}
	}

	for (int i = 0; i < TOTAL_HUMANOIDS; i++)
	{
		if (humanoids[i].isActive())
		{
			if (!freezeActors)
			{
				humanoids[i].update(&landscape);
			}
			humanoids[i].render(camera.worldToScreenPos(humanoids[i].worldPos));

			if (!freezeActors)
			{
				humanoids[i].collisionCheck(playerShots, &playerShip);
			}
		}
	}

	for (int i = 0; i < TOTAL_LANDERS; i++)
	{
		if (landers[i].isActive())
		{
			if (!freezeActors)
			{
				landers[i].update(&landscape, &playerShip);
			}

			landers[i].render(camera.worldToScreenPos(landers[i].worldPos));

			if (!freezeActors)
			{
				landers[i].collisionCheck(playerShots, &playerShip);
			}
		}
	}

	for (int i = 0; i < TOTAL_ENEMY_SHOTS; i++)
	{
		if (enemyShots[i].isActive())
		{
			if (!freezeActors)
			{
				enemyShots[i].update(&playerShip);
			}

			enemyShots[i].render(camera.worldToScreenPos(enemyShots[i].worldPos));

			if (!freezeActors)
			{
				enemyShots[i].collisionCheck(&playerShip);
			}
		}
	}

	for (int i = 0; i < TOTAL_PARTICLES; i++)
	{
		if (particles[i].isActive())
		{
			particles[i].update();
			particles[i].render(camera.worldToScreenPos(particles[i].worldPos));
		}
	}
}

void GameState::spawnWave(uint8_t maxForLevel)
{
	uint8_t toSpawn = maxForLevel - spawnedLanders;
	if (toSpawn > 4)
	{
		toSpawn = 4;
	}

#ifdef _DEBUG
		Serial.print(F("Attempting to spawn "));
		Serial.println(toSpawn);
#endif

	for (uint8_t i = 0; i < toSpawn; i++)
	{
		startSpawningLander();
	}
	spawnCountdown = SPAWN_INTERVAL;
}

PlayerShot* GameState::getPlayerShot()
{
	PlayerShot* pShot = NULL;
	for (uint8_t i = 0; i < TOTAL_PLAYER_SHOTS; i++)
	{
		if (!playerShots[i].isActive())
		{
			pShot = &playerShots[i];
			break;
		}
	}

	return pShot;
}

EnemyShot* GameState::getEnemyShot()
{
	EnemyShot* pShot = NULL;
	for (uint8_t i = 0; i < TOTAL_ENEMY_SHOTS; i++)
	{
		if (!enemyShots[i].isActive())
		{
			pShot = &enemyShots[i];
			break;
		}
	}

	return pShot;
}

Particles* GameState::getParticles()
{
	Particles* pParticles = NULL;
	for (int i = 0; i < TOTAL_PARTICLES; i++)
	{
		if (!particles[i].isActive())
		{
			pParticles = &particles[i];
			break;
		}
	}

	return pParticles;
}

void GameState::lostLife()
{
	unsetFlag(FLAG_FREEZE_ACTORS);
	lives--;

	if (lives > 0)
	{
		playerShip.worldPos.x = playerShip.worldPos.y = 0;
		playerShip.setActive(true);
		camera.worldPos.x = 32;

		// All remaining enemies should be moved
		for (int i = 0; i < TOTAL_LANDERS; i++)
		{
			if (landers[i].isActive())
			{
				landers[i].worldPos.x = getSafeLanderSpawn();
				landers[i].worldPos.y = LANDER_SPAWN_ALT;
			}

			if (!landers[i].isMutant())
			{
				landers[i].startSeeking();
			}
		}
	}
	else
	{
		stateManager.setState(new GameOverState());
	}
}

void GameState::freezeActors()
{
	setFlag(FLAG_FREEZE_ACTORS);
}

void GameState::completeSpawningLander(int xPos, int yPos)
{
	// Find the first inactive lander in the list, activate and place it.
	for (int i = 0; i < TOTAL_LANDERS; i++)
	{
		if (!landers[i].isActive())
		{
			landers[i].setActive(true);
			landers[i].worldPos.x = xPos;
			landers[i].worldPos.y = yPos;
			spawnedLanders++;
			liveEnemiesRemaining++;
			return;
		}
	}
	
#ifdef _DEBUG
	Serial.println(F("Tried to get lander after spawn particles completed, but none was available."));
#endif

}

// Get the index of a humanoid that can be captured, or NO_HUMANOID_FOUND if there is none.
uint8_t GameState::getCapturableHumanoidAtPosition(uint16_t xPos)
{
	uint8_t index = NO_HUMANOID_FOUND;

	for (uint8_t i = 0; i < TOTAL_HUMANOIDS; i++)
	{
		if (humanoids[i].isCapturable() && (uint16_t)(humanoids[i].worldPos.x) == xPos)
		{
			index = i;
			break;
		}
	}

	return index;
}

Humanoid* GameState::getHumanoid(uint8_t index)
{
	return &humanoids[index];
}
