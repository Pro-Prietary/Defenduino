#pragma once

#include "GameObject.h"
#include "Vector2.h"

class MovingGameObject : public GameObject
{
public:
	void update();
	Vector2Int velocity;
};