#include "PlayerShip.h"
#include "Globals.h"

const unsigned char spriteRight[] PROGMEM = { 0x2, 0x7, 0x7, 0x6, 0x6, 0x2, 0x2, 0x2, };
const unsigned char spriteLeft[] PROGMEM = { 0x2, 0x2, 0x2, 0x6, 0x6, 0x7, 0x7, 0x2, };


PlayerShip::PlayerShip() : GameObject()
{
	renderer.setSpriteData(spriteRight);
	pRenderer = &renderer;
	worldPos.x = worldPos.y = 32;
}

void PlayerShip::update()
{
	GameObject::update();

	if (arduboy.pressed(UP_BUTTON)) 
	{
		velocity.y = -1;
	} 
	else if (arduboy.pressed(DOWN_BUTTON)) 
	{
		velocity.y = 1;
	}
	else
	{
		velocity.y = 0;
	}
}