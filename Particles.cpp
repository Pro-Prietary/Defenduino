#include "Particles.h"
#include "Globals.h"

#define FLAG_SPAWNING 0x4
#define FLAG_SPAWNING_BAITER 0x8
#define FLAG_INVERTED 0x10
#define FLAG_PLAYER 0x20

#define MAX_DISTANCE_SMALL 32
#define MAX_DISTANCE_LARGE 128

void Particles::show(uint8_t type)
{
	GameObject::setActive(true);

	unsetFlag(&flags, FLAG_PLAYER);
	unsetFlag(&flags, FLAG_SPAWNING);
	distance = 0;

	if (type == PARTICLES_SPAWN || type == PARTICLES_SPAWN_BAITER)
	{
		setFlag(&flags, FLAG_SPAWNING);

		if (type == PARTICLES_SPAWN_BAITER)
		{
			setFlag(&flags, FLAG_SPAWNING_BAITER);
		}

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
		distance--;

		if (distance <= 0)
		{
			unsetFlag(&flags, FLAG_ACTIVE);

			if (isFlagSet(flags, FLAG_SPAWNING_BAITER))
			{
				pGameState->completeSpawningBaiter(worldPos.x, worldPos.y);
			}
			else
			{
				pGameState->completeSpawningLander(worldPos.x, worldPos.y);
			}
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
	if (distance > 0)
	{
		int halfDist = distance / 2;
		int leftEdge = screenPos.x - halfDist;
		int rightEdge = screenPos.x + halfDist;

		if ((leftEdge < SCREEN_WIDTH && leftEdge >= 0) ||
			(rightEdge < SCREEN_WIDTH && rightEdge >= 0))
		{
			for (int x = -distance; x <= distance; x += distance)
			{
				for (int y = -distance; y <= distance; y += distance)
				{
					if (x != 0 || y != 0)
					{
						arduboy.drawPixel(screenPos.x + x, screenPos.y + y);
					}
				}
			}
		}
	}
}