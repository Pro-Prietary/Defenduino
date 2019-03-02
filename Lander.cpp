#include "Lander.h"
#include "Globals.h"

const unsigned char landerSprite[] PROGMEM = { 0x7, 0x8, 0x24, 0x16, 0xd, 0x3f, 0xd, 0x16, 0x24, };
const unsigned char mutantSprite[] PROGMEM = { 0x7, 0x8, 0x24, 0x16, 0x9, 0x31, 0x9, 0x16, 0x24, };

#define FLAG_SEEKING 0x4
#define FLAG_LANDING 0x8
#define FLAG_ESCAPING 0x10
#define FLAG_MUTANT 0x20

#define LANDER_HORIZ_SPEED 35
#define MUTANT_HORIZ_SPEED 65

#define CRUISING_ALTITUDE 10

#define LANDER_SCORE 150

Lander::Lander() : MovingGameObject()
{

}

void Lander::update(Landscape* pLandscape, PlayerShip* pPlayerShip)
{
	MovingGameObject::update();

	if (isFlagSet(flags, FLAG_SEEKING))
	{
		seekingUpdate(pLandscape, pPlayerShip);
	} 
	else if (isFlagSet(flags, FLAG_LANDING))
	{
		landingUpdate(pPlayerShip);
	}
	else if (isFlagSet(flags, FLAG_ESCAPING))
	{
		escapingUpdate(pPlayerShip);
	}
	else if (isFlagSet(flags, FLAG_MUTANT))
	{
		mutantUpdate(pPlayerShip);
	}
}

void Lander::seekingUpdate(Landscape* pLandscape, PlayerShip* pPlayerShip)
{

	uint8_t landscapeHeight = pLandscape->getHeight(worldPos.x);
	int preferredHeight;
	// Convert to camera space and sub 11  so we keep above it
	int convertedLandscapeHeight = landscapeHeight - 43;

	if (convertedLandscapeHeight < CRUISING_ALTITUDE)
	{
		preferredHeight = convertedLandscapeHeight;
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
		humanoid = ((GameState*)(getCurrentState()))->getCapturableHumanoidAtPosition(worldPos.x+3);

		if (humanoid != NO_HUMANOID_FOUND)
		{
			unsetFlag(&flags, FLAG_SEEKING);
			setFlag(&flags, FLAG_LANDING);

			velocity.x = 0;
			velocity.y = 50;
		}
	}

	// 1/128 chance we'll fire
	if (isFlagSet(flags, FLAG_VISIBLE) && rand() % 128 == 0)
	{
		fire(pPlayerShip);
	}
}

void Lander::landingUpdate(PlayerShip* pPlayerShip)
{
	Humanoid* pHumanoid = ((GameState*)(getCurrentState()))->getHumanoid(humanoid);

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
			unsetFlag(&flags, FLAG_LANDING);
			setFlag(&flags, FLAG_ESCAPING);

			velocity.y = -50;
		}

		// 1/100 chance we'll fire
		if (isFlagSet(flags, FLAG_VISIBLE) && rand() % 100 == 0)
		{
			fire(pPlayerShip);
		}
	}
}

void Lander::escapingUpdate(PlayerShip* pPlayerShip)
{
	Humanoid* pHumanoid = ((GameState*)(getCurrentState()))->getHumanoid(humanoid);
	pHumanoid->worldPos.y = worldPos.y + 8;
	
	if (worldPos.y <= -38)
	{
#ifdef _DEBUG
		Serial.print(F("Lander escaped"));
#endif
		// Escaped off the top of the screen with no humanoid
		((GameState*)(getCurrentState()))->liveEnemiesRemaining--;
		setActive(false);
	} 
	else if (worldPos.y <= -32 && pHumanoid->isActive())
	{
#ifdef _DEBUG
		Serial.println(F("Mutant time!"));
#endif
		// Mutant time!
		pHumanoid->destroy();
		unsetFlag(&flags, FLAG_ESCAPING);
		setFlag(&flags, FLAG_MUTANT);
	}

	// 1/100 chance we'll fire
	if (isFlagSet(flags, FLAG_VISIBLE) && rand() % 100 == 0)
	{
		fire(pPlayerShip);
	}
}

void Lander::mutantUpdate(PlayerShip* pPlayerShip)
{
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

	// 1/64 chance we'll fire
	if (isFlagSet(flags, FLAG_VISIBLE) && rand() % 64 == 0)
	{
		fire(pPlayerShip);
	}
}

bool Lander::render(Vector2Int screenPos)
{
	bool isVisible;
	if (renderSprite(isFlagSet(flags, FLAG_MUTANT) ? mutantSprite : landerSprite, screenPos))
	{
		isVisible = true;
		setFlag(&flags, FLAG_VISIBLE);
	}
	else
	{
		isVisible = false;
		unsetFlag(&flags, FLAG_VISIBLE);
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
	unsetFlag(&flags, FLAG_LANDING);
	unsetFlag(&flags, FLAG_ESCAPING);
	unsetFlag(&flags, FLAG_MUTANT);
	setFlag(&flags, FLAG_SEEKING);

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
		if (pPlayerShots[i].isActive() && pPlayerShots[i].tipOnScreen() && arduboy.collide(pPlayerShots[i].getCollisionRect(), thisRect))
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
	GameState* pGameState = ((GameState*)(getCurrentState()));
	unsetFlag(&flags, FLAG_ACTIVE);
	Particles* pExplosion = pGameState->getParticles();
	if (pExplosion != NULL)
	{
		pExplosion->worldPos.x = worldPos.x;
		pExplosion->worldPos.y = worldPos.y;
		pExplosion->show(PARTICLES_EXPLOSION);
		((GameState*)(getCurrentState()))->liveEnemiesRemaining--;
	}

	if (isFlagSet(flags, FLAG_ESCAPING) && humanoid != NO_HUMANOID_FOUND)
	{
		Humanoid* pHumanoid = pGameState->getHumanoid(humanoid);
		humanoid = NO_HUMANOID_FOUND;

		if (pHumanoid->isActive())
		{
			pHumanoid->startFalling();
		}
	}

	pGameState->score += LANDER_SCORE;
}

bool Lander::isMutant()
{
	return isFlagSet(flags, FLAG_MUTANT);
}

void Lander::fire(PlayerShip* pPlayerShip) {
	EnemyShot* pShot = ((GameState*)(getCurrentState()))->getEnemyShot();

	if (pShot != NULL)
	{
		pShot->fire(pPlayerShip, worldPos);
	}
}
