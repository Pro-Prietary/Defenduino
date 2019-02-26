#include "EnemyShot.h"
#include "Globals.h"

const unsigned char shotSprite[] PROGMEM = { 0x2, 0x7, 0x2, };

#define SHOT_VELOCITY 150

#define FLAG_CHASER 0x4


EnemyShot::EnemyShot() : MovingGameObject()
{
	setSpriteData(shotSprite, 3, 3);
}

void EnemyShot::update(PlayerShip* pPlayerShip)
{
	MovingGameObject::update();
	
	if (isFlagSet(FLAG_CHASER))
	{
		velocity.x = baseVelX + pPlayerShip->velocity.x;
	}
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

void EnemyShot::fire(PlayerShip* pPlayerShip, Vector2 startPos)
{
	worldPos = startPos;

	Vector2 dir = pPlayerShip->worldPos - startPos;
	Vector2 normalized = dir.normalize();

	velocity = Vector2Int(SHOT_VELOCITY * normalized.x, SHOT_VELOCITY * normalized.y);

	// Now add some randomness
	int miss = (rand() % 10) - 20;

	velocity.x += miss;
	velocity.y -= miss;

	setFlag(FLAG_ACTIVE);

	baseVelX = velocity.x;

	// 50% chance this will be a chaser
	setFlag(FLAG_CHASER, arduboy.frameCount % 2 == 0);
	
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