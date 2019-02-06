#pragma once
#include "GameObject.h"

class PlayerShot : public GameObject
{
public:
	void fire(bool right);
	virtual void render(Vector2Int screenPos);
	virtual void update();

private:
	byte length;
};