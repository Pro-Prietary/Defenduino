#include "Lander.h"
#include "Globals.h"

const unsigned char landerSprite[] PROGMEM = { 0x24, 0x16, 0xd, 0x3f, 0xd, 0x16, 0x24, };

#define FLAG_SEEKING 0x4
#define FLAG_LANDING 0x8
#define FLAG_ESCAPING 0x10
#define FLAG_MUTANT 0x20

#define LANDER_HORIZ_SPEED 35
#define CRUISING_ALTITUDE 10

Lander::Lander() : MovingGameObject()
{
	setSpriteData(landerSprite, 7, 6);
}

void Lander::update(Landscape* pLandscape)
{
	MovingGameObject::update();

	if (isFlagSet(FLAG_SEEKING))
	{
		seekingUpdate(pLandscape);
	}
}

void Lander::seekingUpdate(Landscape* pLandscape)
{
	byte landscapeHeight = pLandscape->getHeight(worldPos.x);
	byte preferredHeight;
	// Convert to camera space and sub 11  so we keep above it
	landscapeHeight -= 43;

	if (landscapeHeight < CRUISING_ALTITUDE)
	{
		preferredHeight = landscapeHeight;
	}
	else
	{
		preferredHeight = CRUISING_ALTITUDE;
	}

	if (worldPos.y < preferredHeight)
	{
		worldPos.y+=0.5f;
	}
	else if(worldPos.y > preferredHeight)
	{
		worldPos.y--;
	}
}

bool Lander::render(Vector2Int screenPos)
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

void Lander::setActive(bool active)
{
	GameObject::setActive(active);

	if (active)
	{
		startSeeking();
	}
}

void Lander::startSeeking()
{
	unsetFlag(FLAG_LANDING);
	unsetFlag(FLAG_ESCAPING);
	unsetFlag(FLAG_MUTANT);
	setFlag(FLAG_SEEKING);

	if (rand() % 3 == 0)
	{
		velocity.x = -LANDER_HORIZ_SPEED;
	}
	else
	{
		velocity.x = LANDER_HORIZ_SPEED;
	}
}

void Lander::collisionCheck(PlayerShot* pPlayerShots, PlayerShip* pPlayerShip)
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

	if (pPlayerShip->isActive() and !pPlayerShip->isExploding() && arduboy.collide(pPlayerShip->getCollisionRect(), thisRect))
	{
		destroy();
		pPlayerShip->destroy();
	}
}

Rect Lander::getCollisionRect()
{
	return Rect(worldPos.x, worldPos.y, 7, 6);
}

void Lander::destroy()
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

bool Lander::isMutant()
{
	return isFlagSet(FLAG_MUTANT);
}

