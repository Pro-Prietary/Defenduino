#include "GameState.h"
#include "StateManager.h"
#include "Globals.h"


const byte segmentPoints[8][8] PROGMEM = { { 0,45, 10,60, 100,50, 127,45 },
{ 0,45, 20,48, 100,60, 127,55 },
{ 0,55, 40,60, 115,61, 127,44 },
{ 0,44, 10,60, 100,50, 127,45 },
{ 0,45, 25,50, 75,57,  127,60 },
{ 0,60, 72,60, 100,60, 127,55 },
{ 0,55, 40,60, 115,61, 127,45 },
{ 0,45, 25,55, 98,60, 127,45 } };

GameState::GameState() : State(&camera)
{
	playerShip.setActive(true);
	for (int i = 0; i < TOTAL_LANDSCAPE_SEGMENTS; i++)
	{
		landscapeSegments[i].setData(segmentPoints[i]);
		landscapeSegments[i].worldPos.x = i * 128;
		landscapeSegments[i].setActive(true);
	}

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
		camera.render(&playerShip);
	}

	for (int i = 0; i < TOTAL_LANDSCAPE_SEGMENTS; i++)
	{
		camera.render(&landscapeSegments[i]);
	}

	for (int i = 0; i < TOTAL_HUMANOIDS; i++)
	{
		if (humanoids[i].isActive())
		{
			humanoids[i].update();
			camera.render(&humanoids[i]);
		}
	}

	for (int i = 0; i < TOTAL_PLAYER_SHOTS; i++)
	{
		if (playerShots[i].isActive())
		{
			playerShots[i].update();
			camera.render(&playerShots[i]);
		}
	}

	for (int i = 0; i < TOTAL_LANDERS; i++)
	{
		if (landers[i].isActive())
		{
			landers[i].update();
			camera.render(&landers[i]);
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
