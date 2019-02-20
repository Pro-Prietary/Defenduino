#pragma once

#include "GameObject.h"

class Particles : public GameObject
{
public:
	void show(bool implosion, bool invertScreen, bool large = false);
	void update();
	void render(Vector2Int cameraPos);

private:
	byte distance;
};