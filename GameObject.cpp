#include "GameObject.h"
#include "Globals.h"

GameObject::GameObject()
{
	worldPos.x = worldPos.y = 0;
}

void GameObject::update()
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

void GameObject::render(Vector2Int screenPos)
{
	if (pRenderer != NULL)
	{
		pRenderer->render(screenPos);
	}
}

