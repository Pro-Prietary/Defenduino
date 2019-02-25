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
	void update(Landscape* pLandscape, PlayerShip* pPlayerShip);
	bool render(Vector2Int cameraPos);
	void setActive(bool active);
	void collisionCheck(PlayerShot* playerShots, PlayerShip* pPlayerShip);
	void startSeeking();
	bool isMutant();


private:
	void seekingUpdate(Landscape* pLandscape);
	void landingUpdate();
	void escapingUpdate();
	void mutantUpdate(PlayerShip* pPlayerShip);

	Rect getCollisionRect();
	void destroy();

	uint8_t humanoid;
};