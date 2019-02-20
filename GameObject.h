#pragma once
#include <Arduboy2.h>
#include "Renderer.h"
#include "Vector2.h"
#include "Vector2Int.h"

#define FLAG_ACTIVE 0x1
#define FLAG_VISIBLE 0x2

class GameObject
{
public:
	Vector2 worldPos;
	bool isActive();
	bool isVisible();
	void setActive(bool bActive);

protected:
	GameObject();
	byte flags = 0;
	bool isFlagSet(byte flagToCheck);
	void setFlag(byte flagToSet);
	void unsetFlag(byte flagToUnset);
	void setFlag(byte flagToSet, bool setValue);
}; 


