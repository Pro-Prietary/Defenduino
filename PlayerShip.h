#pragma once
#include "MovingGameObject.h"
#include "Sprite.h"

class PlayerShip : public MovingGameObject, public Sprite
{
private:
	bool facingRight = true;
	void fire();

public:
	PlayerShip();
	void update();
	float getCameraTarget();
	void setActive(bool active);
};