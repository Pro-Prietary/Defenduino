#pragma once

#include "GameObject.h"

class Particles : public GameObject
{
public:
	void show(bool implosion);
	void update();
	void render(Vector2Int cameraPos);

private:
	byte distance;
};