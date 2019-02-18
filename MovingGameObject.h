#pragma once

#include "GameObject.h"
#include "Vector2.h"

class MovingGameObject : public GameObject
{
protected:
	void update();

public:
	Vector2Int velocity;
};