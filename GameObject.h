#pragma once
#include <Arduboy2.h>
#include "Renderer.h"
#include "Vector2.h"
#include "Flaggable.h"

#define FLAG_ACTIVE 0x1
#define FLAG_VISIBLE 0x2

class GameObject : public Flaggable
{
public:
	Vector2 worldPos;
	bool isActive();
	bool isVisible();
	void setActive(bool bActive);

protected:
	GameObject();
}; 


