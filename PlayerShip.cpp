#include "PlayerShip.h"
#include "Globals.h"

const unsigned char spriteData[] PROGMEM = { 0x2, 0x7, 0x7, 0x6, 0x6, 0x2, 0x2, 0x2, };

PlayerShip::PlayerShip()
{
	renderer.setSpriteData(spriteData);
	pRenderer = &renderer;
}

void PlayerShip::update()
{
	GameObject::update();
}