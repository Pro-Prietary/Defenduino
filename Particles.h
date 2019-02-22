#pragma once

#include "GameObject.h"

#define PARTICLES_EXPLOSION 0
#define PARTICLES_SPAWN 1
#define PARTICLES_PLAYER 2

class Particles : public GameObject
{
public:
	void show(byte type);
	void update();
	void render(Vector2Int cameraPos);

private:
	byte distance;
};