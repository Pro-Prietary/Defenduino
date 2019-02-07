#include "GameObject.h"
#include "Globals.h"

GameObject::GameObject()
{
	worldPos.x = worldPos.y = 0;
}

void GameObject::update()
{
}

void GameObject::render(Vector2Int screenPos)
{
	if (pRenderer != NULL)
	{
		pRenderer->render(screenPos);
	}
}

