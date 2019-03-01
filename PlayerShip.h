#pragma once
#include "MovingGameObject.h"
#include "Sprite.h"

class PlayerShip : public MovingGameObject, public Sprite
{
private:
	void fire();
	void activeUpdate();
	void explodingUpdate();
	void explode();


public:
	PlayerShip();
	void update();
	void render(Vector2Int cameraPos);
	float getCameraTarget();
	void destroy();
	Rect getCollisionRect();
	byte explosionTimer = 0;
	void setActive(bool active);
	bool isExploding();
	bool facingRight();
};