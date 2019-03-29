#include "Particles.h"
#include "Globals.h"

#define FLAG_SPAWNING 0x4
#define FLAG_INVERTED 0x8
#define FLAG_PLAYER 0x10

#define MAX_DISTANCE_SMALL 32
#define MAX_DISTANCE_LARGE 128

void Particles::show(uint8_t type)
{
	GameObject::setActive(true);

	unsetFlag(&flags, FLAG_PLAYER);
	unsetFlag(&flags, FLAG_SPAWNING);
	distance = 0;

	if (type == PARTICLES_SPAWN)
	{
		setFlag(&flags, FLAG_SPAWNING);
		distance = MAX_DISTANCE_SMALL;
	}
	else if(type == PARTICLES_PLAYER)
	{
		setFlag(&flags, FLAG_PLAYER);
		arduboy.invert(true);
		setFlag(&flags, FLAG_INVERTED);
	}
}

void Particles::update()
{
	if (isFlagSet(flags, FLAG_SPAWNING))
	{
		distance-=2;
		if (distance <= 0)
		{
			unsetFlag(&flags, FLAG_ACTIVE);
			pGameState->completeSpawningLander(worldPos.x, worldPos.y);
		}
	}
	else
	{
		distance+=2;
		byte maxDistance;
		if (isFlagSet(flags, FLAG_PLAYER))
		{
			maxDistance = MAX_DISTANCE_LARGE;
		}
		else
		{
			maxDistance = MAX_DISTANCE_SMALL;
		}

		if (distance >= maxDistance)
		{
			unsetFlag(&flags, FLAG_ACTIVE);

			if (isFlagSet(flags, FLAG_PLAYER))
			{
				pGameState->lostLife();
			}
		}
	}

	if (isFlagSet(flags, FLAG_INVERTED))
	{
		arduboy.invert(false);
		unsetFlag(&flags, FLAG_INVERTED);
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