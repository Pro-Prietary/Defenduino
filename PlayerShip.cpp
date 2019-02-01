#include "PlayerShip.h"

PlayerShip::PlayerShip()
{
	renderer.setSpriteData(spriteData);
	pRenderer = &renderer;
}