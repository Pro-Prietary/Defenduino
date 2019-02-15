#include "Humanoid.h"
#include "Globals.h"

const unsigned char sprite[] PROGMEM = { 0x7, };

Humanoid::Humanoid() : MovingGameObject()
{
	renderer.setSpriteData(sprite, 1, 3);
}

void Humanoid::update()
{
	MovingGameObject::update();
}

void Humanoid::render(Vector2Int screenPos)
{
	renderer.render(screenPos);
}
