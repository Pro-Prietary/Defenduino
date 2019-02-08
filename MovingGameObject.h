#pragma once

#include "GameObject.h"
#include "Vector2.h"

class MovingGameObject : public GameObject
{
public:
	virtual void update(GameObject* pPrevSibling);

	Vector2Int velocity;
};