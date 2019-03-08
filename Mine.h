#pragma once

#include "GameObject.h"
#include "PlayerShip.h"

class Mine : public GameObject
{
public:
	void update(PlayerShip* pPlayerShip);
	bool render(Vector2Int cameraPos);
	void collisionCheck(PlayerShip* pPlayerShip);
	void destroy();

private:
	Rect getCollisionRect();
};