#pragma once
#include "MovingGameObject.h"

class PlayerShot : public MovingGameObject
{
public:
	void fire(float xVelocity);
	void render(Vector2Int screenPos);
	void update();
	Rect getCollisionRect();

private:
	byte length;
};