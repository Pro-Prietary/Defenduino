#include "GameObject.h"
#include "Globals.h"

GameObject::GameObject()
{
	worldPos.x = worldPos.y = 0;
}

bool GameObject::isActive()
{
	return isFlagSet(FLAG_ACTIVE);
}

bool GameObject::isVisible()
{
	return isFlagSet(FLAG_VISIBLE);
}

void GameObject::setActive(bool bIsActive)
{
	if (bIsActive)
	{
		setFlag(FLAG_ACTIVE);
	}
	else
	{
		unsetFlag(FLAG_ACTIVE);
	}
}

bool GameObject::isFlagSet(byte flagToCheck)
{
	return (flags & flagToCheck) != 0;
}

void GameObject::setFlag(byte flagToSet)
{
	flags = flags | flagToSet;
}

void GameObject::unsetFlag(byte flagToUnset)
{
	flags = flags & ~flagToUnset;
}
