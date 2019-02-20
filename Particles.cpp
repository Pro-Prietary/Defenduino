#include "Particles.h"
#include "Globals.h"

#define FLAG_IMPLODING 0x4
#define FLAG_INVERTED 0x8
#define FLAG_LARGE 0x10

#define MAX_DISTANCE_SMALL 32
#define MAX_DISTANCE_LARGE 128

void Particles::show(bool implosion, bool invertScreen, bool large)
{
	GameObject::setActive(true);

	setFlag(FLAG_LARGE, large);

	if (implosion)
	{
		setFlag(FLAG_IMPLODING);

		if (large)
		{
			distance = MAX_DISTANCE_LARGE;
		}
		else
		{
			distance = MAX_DISTANCE_SMALL;
		}
	}
	else
	{
		unsetFlag(FLAG_IMPLODING);
		distance = 0;
	}

	if (invertScreen)
	{
		arduboy.invert(true);
		setFlag(FLAG_INVERTED);
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
		byte maxDistance;
		if (isFlagSet(FLAG_LARGE))
		{
			maxDistance = MAX_DISTANCE_LARGE;
		}
		else
		{
			maxDistance = MAX_DISTANCE_SMALL;
		}

		if (distance >= maxDistance)
		{
			unsetFlag(FLAG_ACTIVE);
		}
	}

	if (isFlagSet(FLAG_INVERTED))
	{
		arduboy.invert(false);
		unsetFlag(FLAG_INVERTED);
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