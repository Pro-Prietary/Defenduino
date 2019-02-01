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
	GameObject* pNextSibling = NULL;
	GameObject* pPrevSibling = NULL;
	Vector2 worldPos;
	Vector2 velocity;

protected:
	GameObject();
	Renderer* pRenderer;
}; 


