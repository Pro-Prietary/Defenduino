#include "Particles.h"
#include "Globals.h"

#define FLAG_IMPLODING 0x4

#define MAX_DISTANCE 32

void Particles::show(bool implosion)
{
	GameObject::setActive(true);

	if (implosion)
	{
		setFlag(FLAG_IMPLODING);
		distance = MAX_DISTANCE;
	}
	else
	{
		unsetFlag(FLAG_IMPLODING);
		distance = 0;
	}
}

void Particles::update()
{
	if (isFlagSet(FLAG_IMPLODING))
	{
		distance-=2;
		if (distance <= 0)
		{
			unsetFlag(FLAG_ACTIVE);
		}
	}
	else
	{
		distance+=2;
		if (distance >= MAX_DISTANCE)
		{
			unsetFlag(FLAG_ACTIVE);
		}
	}
}

void Particles::render(Vector2Int screenPos)
{
	// If far from the camera, flip to the other side for wrapping
	if (screenPos.x < -HALF_WORLD_WIDTH)
	{
		screenPos.x += WORLD_WIDTH;
	}
	else if (screenPos.x > HALF_WORLD_WIDTH)
	{
		screenPos.x -= WORLD_WIDTH;
	}

	int halfDist = distance / 2;
	int leftEdge = screenPos.x - halfDist;
	int rightEdge = screenPos.x + halfDist;

	if ((leftEdge < SCREEN_WIDTH && leftEdge >= 0) ||
		(rightEdge < SCREEN_WIDTH && rightEdge >= 0))
	{
		arduboy.drawPixel(screenPos.x - distance, screenPos.y);
		arduboy.drawPixel(screenPos.x + distance, screenPos.y);
		arduboy.drawPixel(screenPos.x, screenPos.y - distance);
		arduboy.drawPixel(screenPos.x , screenPos.y + distance);

		arduboy.drawPixel(screenPos.x - distance, screenPos.y - distance);
		arduboy.drawPixel(screenPos.x + distance, screenPos.y - distance);
		arduboy.drawPixel(screenPos.x + distance, screenPos.y + distance);
		arduboy.drawPixel(screenPos.x - distance, screenPos.y + distance);
	}
}