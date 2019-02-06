#pragma once

#include "Camera.h"
#include "PlayerShip.h"

class GameCamera : public Camera
{
public:
	GameCamera();
	virtual Vector2Int worldToScreenPos(Vector2 worldPos);
	virtual void update();
	int getLeftEdgeWorldCoordinate();
	int getRightEdgeWorldCoordinate();
	void setPlayerShip(PlayerShip* pPlayerShip);

private:
	int leftEdge;
	int rightEdge;
	int topEdge;
	int bottomEdge;
	PlayerShip *pPlayerShip;

};