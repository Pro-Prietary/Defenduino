#include "GameState.h"
#include "StateManager.h"
#include "Globals.h"

GameState::GameState() : State(&camera)
{
	

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
	
	for (int i = 0; i < TOTAL_LANDERS; i++)
	{
		spawnLander(rand() % 1024);
	}
}

void GameState::spawnLander(int worldX)
{
	// Find the first inactive lander in the list
	Lander* pLander = NULL;
	for (int i = 0; i < TOTAL_LANDERS; i++)
	{
		if (!landers[i].isActive())
		{
			pLander = &landers[i];
			break;
		}
	}

	if (pLander != NULL)
	{
		pLander->worldPos.x = worldX;
		pLander->worldPos.y = -20;
		pLander->setActive(true);
	}
#ifdef _DEBUG
	else
	{
		Serial.println("Tried to spawn lander but none are available.");
	}
#endif
}

void GameState::update()
{
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
			playerShots[i].update();
			playerShots[i].render(camera.worldToScreenPos(playerShots[i].worldPos));
		}
	}

	for (int i = 0; i < TOTAL_HUMANOIDS; i++)
	{
		if (humanoids[i].isActive())
		{
			humanoids[i].update(&landscape);
			humanoids[i].render(camera.worldToScreenPos(humanoids[i].worldPos));
			humanoids[i].collisionCheck(playerShots, &playerShip);
		}
	}

	for (int i = 0; i < TOTAL_LANDERS; i++)
	{
		if (landers[i].isActive())
		{
			landers[i].update(&landscape);
			landers[i].render(camera.worldToScreenPos(landers[i].worldPos));
			landers[i].collisionCheck(playerShots, &playerShip);
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

PlayerShot* GameState::getPlayerShot()
{
	PlayerShot* pShot = NULL;
	for (int i = 0; i < TOTAL_PLAYER_SHOTS; i++)
	{
		if (!playerShots[i].isActive())
		{
			pShot = &playerShots[i];
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
		if (!pParticles[i].isActive())
		{
			pParticles = &particles[i];
			break;
		}
	}

	return pParticles;
}

void GameState::lostLife()
{
	lives--;
}