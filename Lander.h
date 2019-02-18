#pragma once

#include "MovingGameObject.h"
#include "Sprite.h"

class Lander : public MovingGameObject, public Sprite
{
public:
	Lander();
	void update();

private:
};