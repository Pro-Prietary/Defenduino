#include "Globals.h"
#include "Enemy.h"

void Enemy::collisionCheck(uint8_t width, uint8_t height, uint16_t score, PlayerShot* pPlayerShots, PlayerShip* pPlayerShip, bool isCounted)
{
	Rect thisRect = Rect(worldPos.x, worldPos.y, width, height);
	if (pPlayerShip->isActive() and !pPlayerShip->isExploding() && arduboy.collide(pPlayerShip->getCollisionRect(), thisRect))
	{
		unsetFlag(&flags, FLAG_ACTIVE);
		pPlayerShip->destroy();
	}

	
	for (int i = 0; i < TOTAL_PLAYER_SHOTS; i++)
	{
		if (pPlayerShots[i].isActive() && pPlayerShots[i].tipOnScreen() && arduboy.collide(pPlayerShots[i].getCollisionRect(), thisRect))
		{
			pPlayerShots[i].setActive(false);
			destroy(score, isCounted);
			return;
		}
	}
	
	if (pPlayerShip->isActive() and !pPlayerShip->isExploding() && arduboy.collide(pPlayerShip->getCollisionRect(), thisRect))
	{
		destroy(score, isCounted);
		pPlayerShip->destroy();
	}
}

void Enemy::destroy(uint16_t score, bool isCounted)
{
	explodeObject(&flags, worldPos, PARTICLES_EXPLOSION);
	pGameState->addToScore(score);

	if (isCounted)
	{
		pGameState->onCountedEnemyDeath();
	}
}