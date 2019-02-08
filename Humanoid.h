#pragma once
#include "MovingGameObject.h"
#include "SpriteRenderer.h"

class Humanoid : public MovingGameObject
{
private:
	SpriteRenderer renderer;

public:
	Humanoid();
	virtual void update(GameObject* pPrevSibling);
};