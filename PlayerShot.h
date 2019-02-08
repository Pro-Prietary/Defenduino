#pragma once
#include "MovingGameObject.h"

class PlayerShot : public MovingGameObject
{
public:
	void fire(float xVelocity);
	virtual void render(Vector2Int screenPos);
	virtual void update(GameObject* pPrevSibling);

private:
	byte length;
	bool shrinking;
};