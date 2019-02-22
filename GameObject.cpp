#include "GameObject.h"
#include "Globals.h"

GameObject::GameObject()
{
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

