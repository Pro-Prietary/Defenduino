#pragma once

#include "MovingGameObject.h"
#include "Sprite.h"
#include "Landscape.h"
#include "PlayerShot.h"
#include "PlayerShip.h"

class Lander : public MovingGameObject, public Sprite
{
public:
	Lander();
	void update(Landscape* pLandscape);
	bool render(Vector2Int cameraPos);
	void setActive(bool active);
	void collisionCheck(PlayerShot* playerShots, PlayerShip* pPlayerShip);


private:
	void startSeeking();
	void seekingUpdate(Landscape* pLandscape);
	Rect getCollisionRect();
	void destroy();
};