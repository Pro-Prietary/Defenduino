#pragma once

#include "Enemy.h"
#include "PlayerShip.h"

class Bomber : public Enemy
{
public:
	void update(PlayerShip* pPlayerShip);
	bool render(Vector2Int cameraPos);
	void onSpawn(Vector2 position, bool right);
	void collisionCheck(PlayerShot* playerShots, PlayerShip* pPlayerShip);
	void destroy();


private:
	void draw(Vector2Int screenPos);
};