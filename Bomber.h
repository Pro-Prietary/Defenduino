#pragma once

#include "MovingGameObject.h"
#include "PlayerShip.h"

class Bomber : public MovingGameObject
{
public:
	void update(PlayerShip* pPlayerShip);
	bool render(Vector2Int cameraPos);
	void onSpawn(Vector2 position, bool right);
	void collisionCheck(PlayerShot* playerShots, PlayerShip* pPlayerShip);
	void destroy();


private:
	void draw(Vector2Int screenPos);
	Rect getCollisionRect();
};