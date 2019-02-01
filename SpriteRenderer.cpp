#include "SpriteRenderer.h"
#include "Globals.h"

SpriteRenderer::SpriteRenderer()
{

}

void SpriteRenderer::setSpriteData(unsigned char newSprite[])
{
	spriteData = newSprite;
}

void SpriteRenderer::render(int16_t cameraX, int16_t cameraY, int16_t objectX, int16_t objectY)
{
	arduboy.drawBitmap(5, 10, (const uint8_t *)spriteData, 8, 3, WHITE);

}