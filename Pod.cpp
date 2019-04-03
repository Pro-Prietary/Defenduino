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
	Enemy::collisionCheck(6, 6, POD_SCORE, pPlayerShots, pPlayerShip, true);
}


void Pod::destroy(bool smartBomb)
{
	if (!smartBomb)
	{
		// Spawn swarmers
	}

	Enemy::destroy(POD_SCORE, true);

}
