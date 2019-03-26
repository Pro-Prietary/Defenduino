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
	bool isVisible;
	if (renderSprite(spriteData, screenPos))
	{
		isVisible = true;
		setFlag(&flags, FLAG_VISIBLE);
	}
	else
	{
		isVisible = false;
		unsetFlag(&flags, FLAG_VISIBLE);
	}
	return isVisible;
}


void Pod::onSpawn(Vector2 position, bool right)
{
	worldPos = position;

	velocity.x = right ? HORIZONTAL_VELOCITY : -HORIZONTAL_VELOCITY;
	velocity.y = rand() % 2 == 0 ? DEFAULT_VERTICAL_VELOCITY : -DEFAULT_VERTICAL_VELOCITY;

}

void Pod::collisionCheck(PlayerShot* pPlayerShots, PlayerShip* pPlayerShip)
{
	Rect thisRect = getCollisionRect();
	for (int i = 0; i < TOTAL_PLAYER_SHOTS; i++)
	{
		if (pPlayerShots[i].isActive() && pPlayerShots[i].tipOnScreen() && arduboy.collide(pPlayerShots[i].getCollisionRect(), thisRect))
		{
			pPlayerShots[i].setActive(false);
			destroy(false);
			return;
		}
	}

	if (pPlayerShip->isActive() and !pPlayerShip->isExploding() && arduboy.collide(pPlayerShip->getCollisionRect(), thisRect))
	{
		destroy(false);
		pPlayerShip->destroy();
	}
}

Rect Pod::getCollisionRect()
{
	return Rect(worldPos.x, worldPos.y, 7, 7);
}

void Pod::destroy(bool smartBomb)
{
	GameState* pGameState = ((GameState*)(getCurrentState()));
	unsetFlag(&flags, FLAG_ACTIVE);
	Particles* pExplosion = pGameState->getParticles();
	if (pExplosion != NULL)
	{
		pExplosion->worldPos.x = worldPos.x;
		pExplosion->worldPos.y = worldPos.y;
		pExplosion->show(PARTICLES_EXPLOSION);
	}

	pGameState->addToScore(POD_SCORE);
	pGameState->onCountedEnemyDeath();

	if (!smartBomb)
	{
		// Spawn swarmers
	}
}
