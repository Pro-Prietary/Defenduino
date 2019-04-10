#include "Globals.h"
#include "Swarmer.h"

const unsigned char spriteData[] PROGMEM = { 0x05, 0x08,0xc, 0xa, 0xf, 0xa, 0xc, };

#define HORIZONTAL_VELOCITY 30
#define DEFAULT_VERTICAL_VELOCITY 10

#define SWARMER_SCORE 150

void Swarmer::update(PlayerShip* pPlayerShip)
{
	MovingGameObject::update();

	// 1/100 chance we'll fire
	if (isFlagSet(flags, FLAG_VISIBLE) && rand() % 100 == 0)
	{
		fireAtPlayer(pPlayerShip, worldPos);
	}
}

bool Swarmer::render(Vector2Int screenPos)
{
	renderSpriteIfVisible(spriteData, &flags, screenPos);
}


void Swarmer::collisionCheck(PlayerShot* pPlayerShots, PlayerShip* pPlayerShip)
{
	if (Enemy::collisionCheck(5, 4, pPlayerShots, pPlayerShip))
	{
		destroy(false);
	}
}


void Swarmer::destroy(bool smartBomb)
{
	Enemy::destroy(SWARMER_SCORE, true);
}

void Swarmer::onSpawn(Vector2 position)
{
	worldPos = position;
	velocity.y = rand() % 2 == 0 ? DEFAULT_VERTICAL_VELOCITY : -DEFAULT_VERTICAL_VELOCITY;
}
