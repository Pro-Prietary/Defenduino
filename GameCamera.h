#pragma once

#include "Camera.h"
#include "PlayerShip.h"

class GameCamera : public Camera
{
public:
	GameCamera();
	Vector2Int worldToScreenPos(Vector2 worldPos);
	void update(PlayerShip* pPlayerShip);

private:
};