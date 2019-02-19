#pragma once
#include "MovingGameObject.h"
#include "Sprite.h"
#include "Landscape.h"
#include "PlayerShot.h"
#include "PlayerShip.h"

class Humanoid : public MovingGameObject, public Sprite
{
public:
	Humanoid();
	void update(Landscape* pLandscape);
	bool render(Vector2Int cameraPos);
	void setActive(bool active);
	void collisionCheck(PlayerShot* playerShots, PlayerShip* pPlayerShip);

private:
	Rect getCollisionRect();
	void destroy();
};