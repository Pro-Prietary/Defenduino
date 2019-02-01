#pragma once
#include "GameObject.h"
#include "SpriteRenderer.h"

class PlayerShip : public GameObject
{
private:
	const unsigned char spriteData[8] PROGMEM  = { 0x2, 0x7, 0x7, 0x6, 0x6, 0x2, 0x2, 0x2, };
	SpriteRenderer renderer;

public:
	PlayerShip();

};