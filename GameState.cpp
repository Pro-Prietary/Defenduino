#include "GameState.h"
#include "Globals.h"
#include "GameOverState.h"

#define LANDER_SPAWN_ALT -20

#define FLAG_FREEZE_ACTORS 0x1
#define FLAG_UI_BOTTOM 0x2

#define SPAWN_INTERVAL 600
#define HUMANOID_SPAWN_Y 29

#define SCORE_BOTTOM_Y 57
#define SCANNER_BOTTOM_Y 52

GameState::GameState() : State()
{
	//arduboy.initRandomSeed();
	srand(arduboy.generateRandomSeed());
	playerShip.setActive(true);

	for (int i = 0; i < TOTAL_HUMANOIDS; i++)
	{
		humanoids[i].worldPos.x = rand() % 1024;
		humanoids[i].worldPos.y = HUMANOID_SPAWN_Y;
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
	bool freezeActors = isFlagSet(flags, FLAG_FREEZE_ACTORS);

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

		setFlag(&flags, FLAG_UI_BOTTOM, playerShip.worldPos.y < -16);
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
				humanoids[i].update(&landscape, &playerShip);
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

	drawGui();

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
	unsetFlag(&flags, FLAG_FREEZE_ACTORS);
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

		// All remaining humanoids should be placed on the ground.
		for (int i = 0; i < TOTAL_HUMANOIDS; i++)
		{
			if (humanoids[i].isActive())
			{
				humanoids[i].worldPos.y = HUMANOID_SPAWN_Y;
				humanoids[i].startWalking();
			}
		}

		// All shots should be removed
		for (int i = 0; i < TOTAL_PLAYER_SHOTS; i++)
		{
			if (playerShots[i].isActive())
			{
				playerShots[i].setActive(false);
			}
		}

		for (int i = 0; i < TOTAL_ENEMY_SHOTS; i++)
		{
			if (enemyShots[i].isActive())
			{
				enemyShots[i].setActive(false);
			}
		}
	}
	else
	{
		setState(new GameOverState());
	}
}

void GameState::freezeActors()
{
	setFlag(&flags, FLAG_FREEZE_ACTORS);
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

void GameState::drawGui()
{
	smallFont.setCursor(0, isFlagSet(flags, FLAG_UI_BOTTOM) ? SCORE_BOTTOM_Y : 0);
	smallFont.print(score);
	drawScanner();
}

void GameState::drawScanner()
{
	int scannerY = isFlagSet(flags, FLAG_UI_BOTTOM) ? SCANNER_BOTTOM_Y : 0;

	arduboy.drawRect(31, scannerY, 66, 12, WHITE);
	scannerY++;
	arduboy.fillRect(32, scannerY, 64, 10, BLACK);

	// Draw lanscape on scanner
	int landscapeIdx = camera.worldPos.x - 512;
	if (landscapeIdx < 0)
	{
		landscapeIdx += 1024;
	}

	for (int i = 0; i < 64; i++)
	{
		byte height = landscape.getHeight(landscapeIdx);

		arduboy.drawPixel(32 + i, scannerY + (height / 6.4));

		landscapeIdx += 16;
		if (landscapeIdx >= 1024)
		{
			landscapeIdx = 0;
		}
	}

	for (int i = 0; i < TOTAL_LANDERS; i++)
	{
		if (landers[i].isActive())
		{
			plotOnScanner(scannerY, &landers[i]);
		}
	}

	for (int i = 0; i < TOTAL_HUMANOIDS; i++)
	{
		if (humanoids[i].isActive())
		{
			plotOnScanner(scannerY, &humanoids[i]);
		}
	}

	// Playership
	int yPos = scannerY + ((playerShip.worldPos.y + 32) / 6.4);

	// Different xpos depending on left or right of cam.
	int xPos = playerShip.facingRight() ? 62 : 65;
	arduboy.drawLine(xPos, yPos, xPos+1, yPos, WHITE);

}

void GameState::plotOnScanner(int scannerY, GameObject* pGameObject)
{
	int xPos = ((pGameObject->worldPos.x - camera.worldPos.x) / 16);
	if (xPos >= 32)
	{
		xPos -= 64;
	}
	else if (xPos <= -32)
	{
		xPos += 64;
	}
	arduboy.drawPixel(xPos + 64, scannerY + ((pGameObject->worldPos.y + 32) / 6.4), WHITE);
}