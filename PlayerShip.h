#pragma once
#include "GameObject.h"
#include "SpriteRenderer.h"

class PlayerShip : public GameObject
{
private:
	SpriteRenderer renderer;
	bool facingRight = true;
	void fire();

public:
	PlayerShip();
	virtual void update();
	float getCameraTarget();
};