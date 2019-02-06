#pragma once
#include "GameObject.h"
#include "SpriteRenderer.h"

class Humanoid : public GameObject
{
private:
	SpriteRenderer renderer;

public:
	Humanoid();
	virtual void update();
};