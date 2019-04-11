#include "Globals.h"
#include "Swarmer.h"

const unsigned char spriteData[] PROGMEM = { 0x05, 0x08,0xc, 0xa, 0xf, 0xa, 0xc, };

#define HORIZONTAL_VELOCITY 50
#define DEFAULT_VERTICAL_VELOCITY 15

#define SWARMER_SCORE 150

void Swarmer::update(PlayerShip* pPlayerShip)
{
	MovingGameObject::update();
	verticalWrap(&worldPos);

	// 1/100 chance we'll fire
	if (isFlagSet(flags, FLAG_VISIBLE) && rand() % 100 == 0)
	{
		fireAtPlayer(pPlayerShip, worldPos);
	}

	if (arduboy.frameCount % 100 == 0)
	{
		setHorizontalVelocity(pPlayerShip);
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

void Swarmer::onSpawn(Vector2 position, PlayerShip* pPlayerShip)
{
	worldPos = position;
	velocity.y = rand() % 2 == 0 ? DEFAULT_VERTICAL_VELOCITY : -DEFAULT_VERTICAL_VELOCITY;
	setHorizontalVelocity(pPlayerShip);
}

void Swarmer::setHorizontalVelocity(PlayerShip* pPlayerShip)
{
	if (pPlayerShip->worldPos.x > worldPos.x)
	{
		velocity.x = HORIZONTAL_VELOCITY;
	}
	else
	{
		velocity.x = -HORIZONTAL_VELOCITY;
	}
}
