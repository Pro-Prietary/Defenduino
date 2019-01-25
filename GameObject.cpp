#include "GameObject.h"

GameObject::GameObject()
{

}

void GameObject::update()
{

}

void GameObject::render(int16_t cameraX, int16_t cameraY)
{
	if (pRenderer != NULL)
	{
		pRenderer->render(cameraX, cameraY, x, y);
	}
}

