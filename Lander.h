#pragma once

#include "MovingGameObject.h"
#include "SpriteRenderer.h"

class Lander : public MovingGameObject
{
public:
	Lander();
	virtual void render(Vector2Int cameraPos);

private:
	SpriteRenderer renderer;
};