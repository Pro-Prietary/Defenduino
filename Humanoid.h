#pragma once
#include "MovingGameObject.h"
#include "Sprite.h"

class Humanoid : public MovingGameObject, public Sprite
{
private:

public:
	Humanoid();
	void update();
	void render(Vector2Int cameraPos);
};