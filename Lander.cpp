#include "Lander.h"
#include "Globals.h"

const unsigned char landerSprite[] PROGMEM = { 0x24, 0x16, 0xd, 0x3f, 0xd, 0x16, 0x24, };
const unsigned char mutantSprite[] PROGMEM = { 0x24, 0x16, 0x9, 0x31, 0x9, 0x16, 0x24, };

#define FLAG_SEEKING 0x4
#define FLAG_LANDING 0x8
#define FLAG_ESCAPING 0x10
#define FLAG_MUTANT 0x20

#define LANDER_HORIZ_SPEED 35
#define MUTANT_HORIZ_SPEED 65

#define CRUISING_ALTITUDE 10

Lander::Lander() : MovingGameObject()
{

}

void Lander::update(Landscape* pLandscape, PlayerShip* pPlayerShip)
{
	MovingGameObject::update();

	if (isFlagSet(FLAG_SEEKING))
	{
		seekingUpdate(pLandscape);
	} 
	else if (isFlagSet(FLAG_LANDING))
	{
		landingUpdate();
	}
	else if (isFlagSet(FLAG_ESCAPING))
	{
		escapingUpdate();
	}
	else if (isFlagSet(FLAG_MUTANT))
	{
		mutantUpdate(pPlayerShip);
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

	// 1/20 chance we'll check for humanoids below
	if (arduboy.frameCount % 20 == 0)
	{
		humanoid = ((GameState*)(stateManager.getCurrentState()))->getCapturableHumanoidAtPosition(worldPos.x+3);

		if (humanoid != NO_HUMANOID_FOUND)
		{
			unsetFlag(FLAG_SEEKING);
			setFlag(FLAG_LANDING);

			velocity.x = 0;
			velocity.y = 50;
		}
	}
}

void Lander::landingUpdate()
{
	Humanoid* pHumanoid = ((GameState*)(stateManager.getCurrentState()))->getHumanoid(humanoid);

	if (!pHumanoid->isCapturable())
	{
		startSeeking();
	}
	else
	{
		worldPos.x = pHumanoid->worldPos.x - 3;
		if (worldPos.y >= pHumanoid->worldPos.y - 6)
		{
			pHumanoid->setCaptured(true);
			unsetFlag(FLAG_LANDING);
			setFlag(FLAG_ESCAPING);

			velocity.y = -50;
		}
	}
}

void Lander::escapingUpdate()
{
	Humanoid* pHumanoid = ((GameState*)(stateManager.getCurrentState()))->getHumanoid(humanoid);
	pHumanoid->worldPos.y = worldPos.y + 6;
	
	if (worldPos.y <= -38)
	{
#ifdef _DEBUG
		Serial.print(F("Lander escaped"));
#endif
		// Escaped off the top of the screen with no humanoid
		((GameState*)(stateManager.getCurrentState()))->liveEnemiesRemaining--;
		setActive(false);
	} 
	else if (worldPos.y <= -32 && pHumanoid->isActive())
	{
#ifdef _DEBUG
		Serial.print(F("Mutant time!"));
#endif
		// Mutant time!
		pHumanoid->destroy();
		setSpriteData(mutantSprite, 7, 6);
		unsetFlag(FLAG_ESCAPING);
		setFlag(FLAG_MUTANT);
	}
}

void Lander::mutantUpdate(PlayerShip* pPlayerShip)
{
#ifdef _DEBUG
	Serial.print(F("Mutant update"));
#endif

	if (pPlayerShip->worldPos.x < worldPos.x)
	{
		velocity.x = -LANDER_HORIZ_SPEED;
	}
	else
	{
		velocity.x = LANDER_HORIZ_SPEED;
	}

	if (pPlayerShip->worldPos.y < worldPos.y)
	{
		velocity.y = -100;
	}
	else
	{
		velocity.y = 100;
	}

	// Chance to add some "wiggle"
	if (rand() % 3 == 1)
	{
		velocity.y *= -1;
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
		setSpriteData(landerSprite, 7, 6);
		startSeeking();
	}
}

void Lander::startSeeking()
{
	unsetFlag(FLAG_LANDING);
	unsetFlag(FLAG_ESCAPING);
	unsetFlag(FLAG_MUTANT);
	setFlag(FLAG_SEEKING);

	velocity.y = 0;
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
		((GameState*)(stateManager.getCurrentState()))->liveEnemiesRemaining--;
	}
}

bool Lander::isMutant()
{
	return isFlagSet(FLAG_MUTANT);
}

