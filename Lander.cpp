#include "Lander.h"
#include "Globals.h"

const unsigned char spriteData[] PROGMEM = { 0x24, 0x16, 0xd, 0x3f, 0xd, 0x16, 0x24, };

Lander::Lander() : MovingGameObject()
{
	renderer.setSpriteData(spriteData, 7, 6);
}

void Lander::render(Vector2Int screenPos)
{
	renderer.render(screenPos);
}