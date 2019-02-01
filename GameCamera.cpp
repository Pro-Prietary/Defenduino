#include "GameCamera.h"

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
}

Vector2Int GameCamera::worldToScreenPos(Vector2 objPos)
{
	Vector2Int screenPos;
	screenPos.x = (int)objPos.x - leftEdge;
	screenPos.y = (int)objPos.y - topEdge;
	return screenPos;
}