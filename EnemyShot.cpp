#include "EnemyShot.h"
#include "Globals.h"

const unsigned char shotSprite[] PROGMEM = { 0x2, 0x7, 0x2, };

EnemyShot::EnemyShot() : MovingGameObject()
{
	setSpriteData(shotSprite, 3, 3);
}

bool EnemyShot::render(Vector2Int screenPos)
{
	bool isVisible;
	if (Sprite::render(screenPos))
	{
		isVisible = true;
		setFlag(FLAG_VISIBLE);
	}
	else
	{
		isVisible = false;
		unsetFlag(FLAG_VISIBLE);

		// Turn it off if it goes off the screen
		unsetFlag(FLAG_ACTIVE);
	}
	return isVisible;
}

void EnemyShot::fire(PlayerShip* pPlayerShip)
{

}

void EnemyShot::collisionCheck(PlayerShip* pPlayerShip)
{
	Rect thisRect = getCollisionRect();
	if (pPlayerShip->isActive() and !pPlayerShip->isExploding() && arduboy.collide(pPlayerShip->getCollisionRect(), thisRect))
	{
		unsetFlag(FLAG_ACTIVE);
		pPlayerShip->destroy();
	}
}

Rect EnemyShot::getCollisionRect()
{
	return Rect(worldPos.x, worldPos.y, 3, 3);
}