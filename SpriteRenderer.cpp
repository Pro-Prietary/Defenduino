#include "SpriteRenderer.h"
#include "Globals.h"

SpriteRenderer::SpriteRenderer()
{

}

void SpriteRenderer::setSpriteData(unsigned char newSprite[], int width, int height)
{
	spriteData = newSprite;
	this->width = width;
	this->height = height;
	halfWidth = width / 2;
}

void SpriteRenderer::render(Vector2Int screenPos)
{
	// If far from the camera, flip to the other side for wrapping
	if (screenPos.x < -HALF_WORLD_WIDTH)
	{
		screenPos.x += WORLD_WIDTH;
	}
	else if (screenPos.x > HALF_WORLD_WIDTH)
	{
		screenPos.x -= WORLD_WIDTH;
	}

	GameCamera* pCamera = (GameCamera*)gameState.getCamera();

	int leftEdge = screenPos.x - halfWidth;
	int rightEdge = screenPos.x + halfWidth;

	if ((leftEdge < SCREEN_WIDTH && leftEdge >= 0) ||
		(rightEdge < SCREEN_WIDTH && rightEdge >= 0))
	{
		arduboy.drawBitmap(screenPos.x, screenPos.y, (const uint8_t *)spriteData, width, height, WHITE);
	}

}