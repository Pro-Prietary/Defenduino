#include "Globals.h"
#include "Baiter.h"

const unsigned char spriteData[] PROGMEM = { 0x08, 0x08, 0x2, 0x5, 0x7, 0x5, 0x5, 0x7, 0x5, 0x2, };

#define HORIZONTAL_VELOCITY 50
#define VERTICAL_VELOCITY 15

#define BAITER_SCORE 200

void Baiter::update(PlayerShip* pPlayerShip)
{
	MovingGameObject::update();

	verticalWrap(&worldPos);

	if (arduboy.frameCount % 10 == 0)
	{
		if (arduboy.frameCount % 20 == 0)
		{
			setVelocity(pPlayerShip);
		}
		else
		{
			// 1/100 chance we'll fire
			if (isFlagSet(flags, FLAG_VISIBLE) && rand() % 100 == 0)
			{
				uint16_t xDiff = pPlayerShip->worldPos.x - worldPos.x;
				if ((xDiff > 0 && velocity.x > 0) || (xDiff < 0 && velocity.x < 0))
				{
					fireAtPlayer(pPlayerShip, worldPos);
				}
			}
		}
	}
}

bool Baiter::render(Vector2Int screenPos)
{
	return renderSpriteIfVisible(spriteData, &flags, screenPos);
}

void Baiter::onSpawn(Vector2 position, PlayerShip* pPlayerShip)
{
	worldPos = position;

	setVelocity(pPlayerShip);
}

void Baiter::collisionCheck(PlayerShot* pPlayerShots, PlayerShip* pPlayerShip)
{
	if (Enemy::collisionCheck(8, 3, pPlayerShots, pPlayerShip))
	{
		destroy();
	}
}

void Baiter::destroy()
{
	Enemy::destroy(BAITER_SCORE, false);
}

void Baiter::setVelocity(PlayerShip* pPlayerShip)
{
	if (pPlayerShip->worldPos.x > worldPos.x)
	{
		velocity.x = HORIZONTAL_VELOCITY;
	}
	else
	{
		velocity.x = -HORIZONTAL_VELOCITY;
	}

	velocity.x += pPlayerShip->velocity.x;

	if (pPlayerShip->worldPos.y > worldPos.y)
	{
		velocity.y = VERTICAL_VELOCITY;
	}
	else
	{
		velocity.y = -VERTICAL_VELOCITY;
	}
}
