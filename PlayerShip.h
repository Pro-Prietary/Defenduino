#pragma once
#include "GameObject.h"
#include "SpriteRenderer.h"

class PlayerShip : public GameObject
{
private:
	SpriteRenderer renderer;

public:
	PlayerShip();
	virtual void update();
};