#include "GameObject.h"
#include "Globals.h"

GameObject::GameObject()
{
	worldPos.x = worldPos.y = 0;
}

bool GameObject::isActive()
{
	return bActive;
}

void GameObject::setActive(bool bIsActive)
{
	bActive = bIsActive;
}

