#include "MovingGameObject.h"
#include "Globals.h"

void MovingGameObject::update()
{
	if (velocity.x != 0)
	{
		worldPos.x += velocity.x;
	}

	if (velocity.y != 0)
	{
		worldPos.y += velocity.y;
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