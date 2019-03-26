#pragma once

#include "MovingGameObject.h"
#include "PlayerShip.h"

class Pod : public MovingGameObject
{
public:
	void update(PlayerShip* pPlayerShip);
	bool render(Vector2Int cameraPos);
	void onSpawn(Vector2 position, bool right);
	void collisionCheck(PlayerShot* playerShots, PlayerShip* pPlayerShip);
	void destroy(bool smartBomb);


private:
	Rect getCollisionRect();
};