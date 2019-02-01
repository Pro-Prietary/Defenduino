#include "GameObject.h"

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
}

void GameObject::render(Vector2Int screenPos)
{
	if (pRenderer != NULL)
	{
		pRenderer->render(screenPos);
	}
}

