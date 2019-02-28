#include "Humanoid.h"
#include "Globals.h"

const unsigned char sprite[] PROGMEM = { 0x7, };

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
	setSpriteData(sprite, 1, 3);
}

void Humanoid::update(Landscape* pLandscape, PlayerShip* pPlayerShip)
{
	MovingGameObject::update();

	if (isFlagSet(FLAG_FALLING))
	{
		fallingUpdate(pLandscape);
	}
	else if (isFlagSet(FLAG_CAUGHT))
	{
		caughtUpdate(pLandscape, pPlayerShip);
	}
	else if (!isFlagSet(FLAG_CAPTURED))
	{
		byte landscapeHeight = pLandscape->getHeight(worldPos.x) - 29;

		if (isFlagSet(FLAG_CLIMBER) && landscapeHeight < worldPos.y)
		{
			worldPos.y--;
		}
		else if (landscapeHeight > worldPos.y && worldPos.y < FLOOR)
		{
			worldPos.y++;
		}
	}
}

void Humanoid::onSafeLanding()
{
	unsetFlag(FLAG_FALLING);
	unsetFlag(FLAG_CAUGHT);
	startWalking();
}

void Humanoid::fallingUpdate(Landscape* pLandscape)
{
	velocity.y++;
	byte landscapeHeight = pLandscape->getHeight(worldPos.x) - 29;
	if (worldPos.y >= landscapeHeight)
	{
		// Hit the ground
		if (velocity.y >= 30)
		{
			destroy();
		}
		else
		{
			((GameState*)(stateManager.getCurrentState()))->score += LANDING_SCORE;
			onSafeLanding();
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
		((GameState*)(stateManager.getCurrentState()))->score += DROPPED_SCORE;
		onSafeLanding();
	}
}


bool Humanoid::render(Vector2Int screenPos)
{
	bool isVisible;
	if (Sprite::render(screenPos))
	{
		isVisible = true;
		setFlag(FLAG_VISIBLE);
	}
	else
	{
		isVisible = false;
		unsetFlag(FLAG_VISIBLE);
	}
	return isVisible;
}

void Humanoid::setActive(bool active)
{
	GameObject::setActive(active);
	if (rand() % 2 == 1)
	{
		setFlag(FLAG_CLIMBER);
	}
	else
	{
		unsetFlag(FLAG_CLIMBER);
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
}

void Humanoid::collisionCheck(PlayerShot* pPlayerShots, PlayerShip* pPlayerShip)
{
	if (!isFlagSet(FLAG_CAUGHT))
	{
		Rect thisRect = getCollisionRect();
		for (int i = 0; i < TOTAL_PLAYER_SHOTS; i++)
		{
			if (pPlayerShots[i].isActive() && arduboy.collide(pPlayerShots[i].getCollisionRect(), thisRect))
			{
				pPlayerShots[i].setActive(false);
				destroy();
				return;
			}
		}

		if (isFlagSet(FLAG_FALLING) && arduboy.collide(pPlayerShip->getCollisionRect(), thisRect))
		{
			// Caught
			((GameState*)(stateManager.getCurrentState()))->score += CAUGHT_SCORE;
			unsetFlag(FLAG_FALLING);
			setFlag(FLAG_CAUGHT);
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
	unsetFlag(FLAG_ACTIVE);

	Particles* pExplosion = ((GameState*)(stateManager.getCurrentState()))->getParticles();
	if (pExplosion != NULL)
	{
		pExplosion->worldPos.x = worldPos.x;
		pExplosion->worldPos.y = worldPos.y;
		pExplosion->show(PARTICLES_EXPLOSION);
	}
}

bool Humanoid::isCapturable()
{
	return isActive() && !isFlagSet(FLAG_CAPTURED) && !isFlagSet(FLAG_FALLING);
}

void Humanoid::setCaptured(bool captured)
{
	setFlag(FLAG_CAPTURED, captured);
	velocity.x = 0;
	velocity.y = 0;
}

void Humanoid::startFalling()
{
	unsetFlag(FLAG_CAPTURED);
	setFlag(FLAG_FALLING);
}