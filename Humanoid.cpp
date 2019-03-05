#include "Humanoid.h"
#include "Globals.h"

#define FLOOR 29

#define CAUGHT_SCORE 500
#define DROPPED_SCORE 500
#define LANDING_SCORE 250

#define FLAG_CLIMBER 0x4
#define FLAG_CAPTURED 0x8
#define FLAG_FALLING 0x10
#define FLAG_CAUGHT 0x20

Humanoid::Humanoid() : MovingGameObject()
{
}

void Humanoid::update(Landscape* pLandscape, PlayerShip* pPlayerShip)
{
	MovingGameObject::update();

	if (isFlagSet(flags, FLAG_FALLING))
	{
		fallingUpdate(pLandscape);
	}
	else if (isFlagSet(flags, FLAG_CAUGHT))
	{
		caughtUpdate(pLandscape, pPlayerShip);
	}
	else if (!isFlagSet(flags, FLAG_CAPTURED))
	{
		byte landscapeHeight = pLandscape->getHeight(worldPos.x) - 29;

		if (isFlagSet(flags, FLAG_CLIMBER) && landscapeHeight < worldPos.y)
		{
			worldPos.y--;
		}
		else if (landscapeHeight > worldPos.y && worldPos.y < FLOOR)
		{
			worldPos.y++;
		}
	}
}


void Humanoid::fallingUpdate(Landscape* pLandscape)
{
	velocity.y++;
	byte landscapeHeight = pLandscape->getHeight(worldPos.x) - 29;
	if (worldPos.y >= landscapeHeight)
	{
		// Hit the ground
		if (velocity.y >= 100)
		{
			destroy();
		}
		else
		{
			((GameState*)(getCurrentState()))->addToScore(LANDING_SCORE);
			startWalking();
		}
	}
}

void Humanoid::caughtUpdate(Landscape* pLandscape, PlayerShip* pPlayerShip)
{
	worldPos.x = pPlayerShip->worldPos.x + 3;
	worldPos.y = pPlayerShip->worldPos.y + 4;

	byte landscapeHeight = pLandscape->getHeight(worldPos.x) - 29;
	if (worldPos.y >= landscapeHeight)
	{
		// Dropped off
		((GameState*)(getCurrentState()))->addToScore(DROPPED_SCORE);
		worldPos.y = landscapeHeight;

		// Make sure we're not in the same place as another one.
		while (sameXAsAnotherHuman())
		{
			worldPos.x -= 2;
		}

		startWalking();
	}
}

bool Humanoid::sameXAsAnotherHuman()
{
	GameState* pState = (GameState*)getCurrentState();
	for (uint8_t i = 0; i < TOTAL_HUMANOIDS; i++)
	{
		Humanoid* pHumanoid = pState->getHumanoid(i);
		if (pHumanoid != this && pHumanoid->isActive() && pHumanoid->worldPos.x == worldPos.x)
		{
			return true;
		}
	}
	return false;
}

bool Humanoid::render(Vector2Int screenPos)
{
	bool isVisible;
	if (screenPos.x >= 0 and screenPos.y < SCREEN_WIDTH)
	{
		isVisible = true;
		setFlag(&flags, FLAG_VISIBLE);
		arduboy.drawLine(screenPos.x, screenPos.y, screenPos.x, screenPos.y + 2, WHITE);
	}
	else
	{
		isVisible = false;
		unsetFlag(&flags, FLAG_VISIBLE);
	}
	return isVisible;
}

void Humanoid::setActive(bool active)
{
	GameObject::setActive(active);
	if (rand() % 2 == 1)
	{
		setFlag(&flags, FLAG_CLIMBER);
	}
	else
	{
		unsetFlag(&flags, FLAG_CLIMBER);
	}
	startWalking();
}

void Humanoid::startWalking()
{
	if (rand() % 2 == 0)
	{
		velocity.x = 5;
	}
	else
	{
		velocity.x = -5;
	}
	velocity.y = 0;

	unsetFlag(&flags, FLAG_CAUGHT);
	unsetFlag(&flags, FLAG_CAPTURED);
	unsetFlag(&flags, FLAG_FALLING);
}

void Humanoid::collisionCheck(PlayerShot* pPlayerShots, PlayerShip* pPlayerShip)
{
	if (!isFlagSet(flags, FLAG_CAUGHT))
	{
		Rect thisRect = getCollisionRect();
		for (int i = 0; i < TOTAL_PLAYER_SHOTS; i++)
		{
			if (pPlayerShots[i].isActive() && pPlayerShots[i].tipOnScreen() && arduboy.collide(pPlayerShots[i].getCollisionRect(), thisRect))
			{
				pPlayerShots[i].setActive(false);
				destroy();
				return;
			}
		}

		if (isFlagSet(flags, FLAG_FALLING) && arduboy.collide(pPlayerShip->getCollisionRect(), thisRect))
		{
			// Caught
			((GameState*)(getCurrentState()))->addToScore(CAUGHT_SCORE);
			unsetFlag(&flags, FLAG_FALLING);
			setFlag(&flags, FLAG_CAUGHT);
			velocity.y = 0;
		}
	}
}

Rect Humanoid::getCollisionRect()
{
	return Rect(worldPos.x, worldPos.y, 1, 3);
}

void Humanoid::destroy()
{
	unsetFlag(&flags, FLAG_ACTIVE);

	Particles* pExplosion = ((GameState*)(getCurrentState()))->getParticles();
	if (pExplosion != NULL)
	{
		pExplosion->worldPos.x = worldPos.x;
		pExplosion->worldPos.y = worldPos.y;
		pExplosion->show(PARTICLES_EXPLOSION);
	}
}

bool Humanoid::isCapturable()
{
	return isActive() && !isFlagSet(flags, FLAG_CAPTURED) && !isFlagSet(flags, FLAG_FALLING) && !isFlagSet(flags, FLAG_CAUGHT);
}

void Humanoid::setCaptured(bool captured)
{
	setFlag(&flags, FLAG_CAPTURED, captured);
	velocity.x = 0;
	velocity.y = 0;
}

void Humanoid::startFalling()
{
	unsetFlag(&flags, FLAG_CAPTURED);
	setFlag(&flags, FLAG_FALLING);
}

bool Humanoid::isCarried()
{
	return isFlagSet(flags, FLAG_CAUGHT);
}