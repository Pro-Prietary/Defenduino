#include "Globals.h"
#include "Pod.h"

const unsigned char spriteData[] PROGMEM = { 0x07, 0x08, 0x8, 0x2a, 0x1c, 0x7f, 0x1c, 0x2a, 0x8, };

#define HORIZONTAL_VELOCITY 30
#define DEFAULT_VERTICAL_VELOCITY 10

#define POD_SCORE 1000

void Pod::update(PlayerShip* pPlayerShip)
{
	MovingGameObject::update();

	if (worldPos.y < -40)
	{
		worldPos.y = 31;
	}
	else if (worldPos.y > 31)
	{
		worldPos.y = -40;
	}
}

bool Pod::render(Vector2Int screenPos)
{
	return renderSpriteIfVisible(spriteData, &flags, screenPos);
}


void Pod::onSpawn(Vector2 position, bool right)
{
	worldPos = position;

	velocity.x = right ? HORIZONTAL_VELOCITY : -HORIZONTAL_VELOCITY;
	velocity.y = rand() % 2 == 0 ? DEFAULT_VERTICAL_VELOCITY : -DEFAULT_VERTICAL_VELOCITY;

}

void Pod::collisionCheck(PlayerShot* pPlayerShots, PlayerShip* pPlayerShip)
{
	if (Enemy::collisionCheck(6, 6, pPlayerShots, pPlayerShip))
	{
		destroy(false);
	}
}


void Pod::destroy(bool smartBomb)
{
	Enemy::destroy(POD_SCORE, true);
	if (!smartBomb)
	{
		for (int i = 0; i < 4; i++)
		{
			Swarmer* pSwarmer = pGameState->getSwarmer();
			if (pSwarmer != NULL)
			{
				pSwarmer->setActive(true);
				Vector2 spawnPos(worldPos.x - (4 * i) + 8, worldPos.y - (4 * i) + 8);
				pSwarmer->onSpawn(spawnPos);
			}
		}
	}
	else
	{
		pGameState->onCountedEnemyDeath(4);	// Account for the swarmers dying too
	}

	Enemy::destroy(POD_SCORE, true);

}
