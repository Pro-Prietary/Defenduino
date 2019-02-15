#pragma once
#include "MovingGameObject.h"
#include "SpriteRenderer.h"

class PlayerShip : public MovingGameObject
{
private:
	SpriteRenderer renderer;
	bool facingRight = true;
	void fire();

public:
	PlayerShip();
	virtual void update();
	virtual void render(Vector2Int screenPos);
	float getCameraTarget();
};