#include "Humanoid.h"
#include "Globals.h"

const unsigned char sprite[] PROGMEM = { 0x7, };

#define FLOOR 29

#define FLAG_CLIMBER 0x4

Humanoid::Humanoid() : MovingGameObject()
{
	setSpriteData(sprite, 1, 3);
}

void Humanoid::update(Landscape* pLandscape)
{
	MovingGameObject::update();

	byte landscapeHeight = pLandscape->getHeight(worldPos.x) - 29;

	if (isFlagSet(FLAG_CLIMBER) && landscapeHeight < worldPos.y)
	{
		worldPos.y--;
	}
	else if (landscapeHeight > worldPos.y && worldPos.y < FLOOR)
	{
		worldPos.y++;
	}
}

bool Humanoid::render(Vector2Int screenPos)
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
	}
	return isVisible;
}

void Humanoid::setActive(bool active)
{
	GameObject::setActive(active);
	if (rand() % 2 == 1)
	{
		setFlag(FLAG_CLIMBER);
	}
	else
	{
		unsetFlag(FLAG_CLIMBER);
	}
}

void Humanoid::collisionCheck(PlayerShot* pPlayerShots, PlayerShip* pPlayerShip)
{
	Rect thisRect = getCollisionRect();
	for (int i = 0; i < TOTAL_PLAYER_SHOTS; i++)
	{
		if (pPlayerShots[i].isActive() && arduboy.collide(pPlayerShots[i].getCollisionRect(), thisRect))
		{
			pPlayerShots[i].setActive(false);
			destroy();
			break;
		}
	}
}

Rect Humanoid::getCollisionRect()
{
	return Rect(worldPos.x, worldPos.y, 1, 3);
}

void Humanoid::destroy()
{
	unsetFlag(FLAG_ACTIVE);
}