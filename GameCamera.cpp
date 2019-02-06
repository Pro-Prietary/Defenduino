#include "GameCamera.h"
#include "Globals.h"

#define MAX_CAMERA_SPEED 3

GameCamera::GameCamera() : Camera()
{
	worldPos.x = 32;
}

void GameCamera::update()
{
	Camera::update();

	// Recalculate bounds in world space
	leftEdge = worldPos.x - HALF_SCREEN_WIDTH;
	rightEdge = worldPos.x + HALF_SCREEN_WIDTH;
	topEdge = worldPos.y - HALF_SCREEN_HEIGHT;
	bottomEdge = worldPos.y + HALF_SCREEN_HEIGHT;

	float targetXPos = pPlayerShip->getCameraTarget();

	if (worldPos.x != targetXPos)
	{
		int distance =  targetXPos - worldPos.x;
		// TODO: Handle if target is wrapped around but less than camera speed, to avoid "jump" when crossing the border

		if (distance < 0)
		{
			if (distance < -MAX_CAMERA_SPEED)
			{
				if (distance < -HALF_WORLD_WIDTH)
				{
					// Go the other way if it's quicker to just wrap around
					worldPos.x += MAX_CAMERA_SPEED;
				}
				else
				{
					worldPos.x -= MAX_CAMERA_SPEED;
				}
			}
			else
			{
				worldPos.x = targetXPos;
			}
		}
		else
		{
			if (distance > MAX_CAMERA_SPEED)
			{
				if (distance > HALF_WORLD_WIDTH)
				{
					// Go the other way if it's quicker to just wrap around
					worldPos.x -= MAX_CAMERA_SPEED;
				}
				else
				{
					worldPos.x += MAX_CAMERA_SPEED;

				}
			}
			else
			{
				worldPos.x = targetXPos;
			}
		}

		if (worldPos.x >= WORLD_WIDTH)
		{
			worldPos.x -= WORLD_WIDTH;
		}
		else if (worldPos.x < 0)
		{
			worldPos.x += WORLD_WIDTH;
		}
	}
}

Vector2Int GameCamera::worldToScreenPos(Vector2 objPos)
{
	Vector2Int screenPos;
	screenPos.x = (int)objPos.x - leftEdge;
	screenPos.y = (int)objPos.y - topEdge;
	return screenPos;
}

int GameCamera::getLeftEdgeWorldCoordinate()
{
	return leftEdge;
}

int GameCamera::getRightEdgeWorldCoordinate()
{
	return rightEdge;
}

void GameCamera::setPlayerShip(PlayerShip* pPlayerShip)
{
	this->pPlayerShip = pPlayerShip;
}