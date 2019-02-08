#include "GameObject.h"
#include "Globals.h"

GameObject::GameObject()
{
	worldPos.x = worldPos.y = 0;
}

void GameObject::update(GameObject* pPrevSibling)
{
}

void GameObject::render(Vector2Int screenPos)
{
	if (pRenderer != NULL)
	{
		pRenderer->render(screenPos);
	}
}

