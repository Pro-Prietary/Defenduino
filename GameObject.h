#pragma once
#include <Arduboy2.h>
#include "Renderer.h"
#include "Vector2.h"
#include "Vector2Int.h"


class GameObject
{
public:
	virtual void update(GameObject* pPrevSibling);
	virtual void render(Vector2Int screenPos);
	GameObject* pNextSibling = NULL;
	Vector2 worldPos;


protected:
	GameObject();
	Renderer* pRenderer;
}; 


