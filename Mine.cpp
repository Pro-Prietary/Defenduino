#include "Mine.h"
#include "Globals.h"

const unsigned char spriteData[] PROGMEM = { 0x3, 0x8, 0x5, 0x2, 0x5, };

bool Mine::render(Vector2Int screenPos)
{
	bool bIsVisible = false;
	// If far from the camera, flip to the other side for wrapping
	if (screenPos.x < -HALF_WORLD_WIDTH)
	{
		screenPos.x += WORLD_WIDTH;
	}
	else if (screenPos.x > HALF_WORLD_WIDTH)
	{
		screenPos.x -= WORLD_WIDTH;
	}

	int leftEdge = screenPos.x;
	int rightEdge = screenPos.x + 8;

	if ((leftEdge < SCREEN_WIDTH && leftEdge >= 0) ||
		(rightEdge < SCREEN_WIDTH && rightEdge >= 0))
	{
		renderSprite(spriteData, screenPos);
		bIsVisible = true;
	}
	else
	{
		// Disappear once off the screen
		setActive(false);
	}

	setFlag(&flags, FLAG_VISIBLE, bIsVisible);

	return bIsVisible;
}

void Mine::collisionCheck(PlayerShip* pPlayerShip)
{
	Rect thisRect = getCollisionRect();

	if (pPlayerShip->isActive() and !pPlayerShip->isExploding() && arduboy.collide(pPlayerShip->getCollisionRect(), thisRect))
	{
		setActive(false);
		pPlayerShip->destroy();
	}
}

Rect Mine::getCollisionRect()
{
	return Rect(worldPos.x, worldPos.y, 3, 3);
}