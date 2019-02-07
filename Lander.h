#pragma once

#include "MovingGameObject.h"
#include "SpriteRenderer.h"

class Lander : public MovingGameObject
{
public:
	Lander();

private:
	SpriteRenderer renderer;
};