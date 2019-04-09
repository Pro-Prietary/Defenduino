#pragma once

#include "MovingGameObject.h"
#include "PlayerShip.h"

class Swarmer : public Enemy
{
public:
	void update(PlayerShip* pPlayerShip);
	bool render(Vector2Int cameraPos);
	void collisionCheck(PlayerShot* playerShots, PlayerShip* pPlayerShip);
	void destroy(bool smartBomb);
	void onSpawn(Vector2 position);
};