#include "SpriteRenderer.h"
#include "Globals.h"

SpriteRenderer::SpriteRenderer()
{

}

void SpriteRenderer::setSpriteData(unsigned char newSprite[])
{
	spriteData = newSprite;
}

void SpriteRenderer::render(Vector2Int screenPos)
{
	arduboy.drawBitmap(screenPos.x, screenPos.y, (const uint8_t *)spriteData, 8, 3, WHITE);

}