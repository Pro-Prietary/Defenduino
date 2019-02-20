#include "Sprite.h"
#include "Globals.h"

Sprite::Sprite()
{

}

void Sprite::setSpriteData(unsigned char newSprite[], byte width, byte height)
{
	spriteData = newSprite;
	this->width = width;
	this->height = height;
	halfWidth = width / 2;
}

bool Sprite::render(Vector2Int screenPos)
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

	GameCamera* pCamera = (GameCamera*)(stateManager.getCurrentState()->getCamera());

	int leftEdge = screenPos.x - halfWidth;
	int rightEdge = screenPos.x + halfWidth;

	if ((leftEdge < SCREEN_WIDTH && leftEdge >= 0) ||
		(rightEdge < SCREEN_WIDTH && rightEdge >= 0))
	{
		arduboy.drawBitmap(screenPos.x, screenPos.y, (const uint8_t *)spriteData, width, height, WHITE);
		bIsVisible = true;
	}

	return bIsVisible;
}

