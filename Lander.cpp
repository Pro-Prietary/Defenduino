#include "Lander.h"
#include "Globals.h"

const unsigned char landerSprite[] PROGMEM = { 0x24, 0x16, 0xd, 0x3f, 0xd, 0x16, 0x24, };

Lander::Lander() : MovingGameObject()
{
	setSpriteData(landerSprite, 7, 6);
}

void Lander::update()
{
	MovingGameObject::update();
}