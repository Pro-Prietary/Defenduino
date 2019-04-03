#include "GameCamera.h"
#include "Globals.h"

#define MAX_CAMERA_SPEED 300

GameCamera::GameCamera() : MovingGameObject()
{

}

void GameCamera::update(PlayerShip* pPlayerShip)
{
	MovingGameObject::update();

	float targetXPos = pPlayerShip->getCameraTarget();

	if (worldPos.x != targetXPos)
	{
		int distance =  targetXPos - worldPos.x;
		// TODO: Handle if target is wrapped around but less than camera speed, to avoid "jump" when crossing the border
		float fMaxCameraSpeed = MAX_CAMERA_SPEED / 100.0; 

		if (distance < 0)
		{
			if (distance < -fMaxCameraSpeed)
			{
				if (distance < -HALF_WORLD_WIDTH)
				{
					// Go the other way if it's quicker to just wrap around
					worldPos.x += fMaxCameraSpeed;
				}
				else
				{
					worldPos.x -= fMaxCameraSpeed;
				}
			}
			else
			{
				worldPos.x = targetXPos;
			}
		}
		else
		{
			if (distance > fMaxCameraSpeed)
			{
				if (distance > HALF_WORLD_WIDTH)
				{
					// Go the other way if it's quicker to just wrap around
					worldPos.x -= fMaxCameraSpeed;
				}
				else
				{
					worldPos.x += fMaxCameraSpeed;

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
	screenPos.x = (int)objPos.x - (worldPos.x - HALF_SCREEN_WIDTH);
	screenPos.y = (int)objPos.y + HALF_SCREEN_HEIGHT;

	// If far from the camera, flip to the other side for wrapping
	if (screenPos.x < -HALF_WORLD_WIDTH)
	{
		screenPos.x += WORLD_WIDTH;
	}
	else if (screenPos.x > HALF_WORLD_WIDTH)
	{
		screenPos.x -= WORLD_WIDTH;
	}

	return screenPos;
}

