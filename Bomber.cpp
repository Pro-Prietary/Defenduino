#include "Globals.h"
#include "Bomber.h"

const unsigned char spriteData[] PROGMEM = { 0x08, 0x08, 0xf8, 0xfe, 0xda, 0xfa, 0xfa, 0x42, 0x7e, 0x00, };

#define HORIZONTAL_VELOCITY 50
#define DEFAULT_VERTICAL_VELOCITY 15

#define BOMBER_SCORE 250

void Bomber::update(PlayerShip* pPlayerShip)
{
	MovingGameObject::update();

	if (worldPos.y < -40)
	{
		worldPos.y = 31;
	}
	else if (worldPos.y > 31)
	{
		worldPos.y = -40;
	}

	if (isFlagSet(flags, FLAG_VISIBLE) && rand() % 64 == 0)
	{
		Mine* pMine = pGameState->getMine();
		if (pMine != NULL)
		{
			pMine->setActive(true);
			pMine->worldPos.x = worldPos.x;
			pMine->worldPos.y = worldPos.y;
			Serial.println(F("Mine dropped"));
		}
	}
}

bool Bomber::render(Vector2Int screenPos)
{
	bool bIsVisible = false;
	// If far from the camera, flip to the other side for wrapping
	if (screenPos.x < -HALF_WORLD_WIDTH)
	{
		screenPos.x += WORLD_WIDTH;
	}
	else if (screenPos.x > HALF_WORLD_WIDTH)
	{
		screenPos.x -= WORLD_WIDTH;
	}

	int leftEdge = screenPos.x;
	int rightEdge = screenPos.x + 8;

	if ((leftEdge < SCREEN_WIDTH && leftEdge >= 0) ||
		(rightEdge < SCREEN_WIDTH && rightEdge >= 0))
	{
		draw(screenPos);
		bIsVisible = true;
	}

	setFlag(&flags, FLAG_VISIBLE, bIsVisible);
	return bIsVisible;
}

void Bomber::draw(Vector2Int screenPos)
{
	uint8_t mirror;
	if (velocity.x > 0)
	{
		if (velocity.y > 0)
		{
			mirror = MIRROR_HORIZONTAL;
		}
		else
		{
			mirror = MIRROR_HOR_VER;
		}
	}
	else
	{
		if (velocity.y > 0)
		{
			mirror = MIRROR_NONE;
		}
		else
		{
			mirror = MIRROR_VERTICAL;
		}
	}

	renderSprite(spriteData, screenPos, mirror);
}

void Bomber::onSpawn(Vector2 position, bool right)
{
	worldPos = position;

	velocity.x = right ? HORIZONTAL_VELOCITY : -HORIZONTAL_VELOCITY;
	velocity.y = rand() % 2 == 0 ? DEFAULT_VERTICAL_VELOCITY : -DEFAULT_VERTICAL_VELOCITY;

}

void Bomber::collisionCheck(PlayerShot* pPlayerShots, PlayerShip* pPlayerShip)
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

Rect Bomber::getCollisionRect()
{
	return Rect(worldPos.x, worldPos.y, 8, 8);
}

void Bomber::destroy()
{
	explodeObject(&flags, worldPos, PARTICLES_EXPLOSION);
	pGameState->addToScore(BOMBER_SCORE);
	pGameState->onCountedEnemyDeath();
}
