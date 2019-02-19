#pragma once
#include "MovingGameObject.h"
#include "Sprite.h"

class PlayerShip : public MovingGameObject, public Sprite
{
private:
	void fire();

public:
	PlayerShip();
	void update();
	void render(Vector2Int cameraPos);
	float getCameraTarget();
};