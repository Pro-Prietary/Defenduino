#include "PlayerShip.h"
#include "Globals.h"

const unsigned char spriteRight[] PROGMEM = { 0x2, 0x7, 0x7, 0x6, 0x6, 0x2, 0x2, 0x2, };
const unsigned char spriteLeft[] PROGMEM = { 0x2, 0x2, 0x2, 0x6, 0x6, 0x7, 0x7, 0x2, };


PlayerShip::PlayerShip() : GameObject()
{
	renderer.setSpriteData(spriteRight);
	pRenderer = &renderer;
	worldPos.x = worldPos.y = 0;
}

void PlayerShip::update()
{
	GameObject::update();

	if (arduboy.pressed(UP_BUTTON) && worldPos.y > -HALF_SCREEN_HEIGHT) 
	{
		worldPos.y--;
	} 
	else if (arduboy.pressed(DOWN_BUTTON) && worldPos.y < HALF_SCREEN_HEIGHT - 3)
	{
		worldPos.y++;
	}
}