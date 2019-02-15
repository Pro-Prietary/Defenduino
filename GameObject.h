#pragma once
#include <Arduboy2.h>
#include "Renderer.h"
#include "Vector2.h"
#include "Vector2Int.h"


class GameObject
{
public:
	virtual void update();
	virtual void render(Vector2Int screenPos);
	Vector2 worldPos;
	bool isActive();
	void setActive(bool bActive);

protected:
	GameObject();
	bool bActive = false;
}; 


