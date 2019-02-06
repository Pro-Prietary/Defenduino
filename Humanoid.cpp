#include "Humanoid.h"
#include "Globals.h"

const unsigned char sprite[] PROGMEM = { 0x7, };

Humanoid::Humanoid() : GameObject()
{
	renderer.setSpriteData(sprite, 1, 3);
	pRenderer = &renderer;
}

void Humanoid::update()
{
	GameObject::update();

	
}
