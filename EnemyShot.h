#pragma once

#include "MovingGameObject.h"
#include "Sprite.h"
#include "PlayerShip.h"

class EnemyShot : public MovingGameObject, public Sprite
{
public:
	EnemyShot();
	bool render(Vector2Int screenPos);
	void fire(PlayerShip* pPlayerShip, Vector2 startPos);
	void collisionCheck(PlayerShip* pPlayerShip);
	void update(PlayerShip* pPlayerShip);

private:
	Rect getCollisionRect();
	uint16_t baseVelX;
};