#include "MovingGameObject.h"
#include "Globals.h"

void MovingGameObject::update(GameObject* pPrevSibling)
{
	if (velocity.x != 0)
	{
		worldPos.x += velocity.x / 100.0;
	}

	if (velocity.y != 0)
	{
		worldPos.y += velocity.y / 100.0;
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