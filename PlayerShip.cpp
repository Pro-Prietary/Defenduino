#include "PlayerShip.h"
#include "Globals.h"

const unsigned char spriteRight[] PROGMEM = { 0x8, 0x8, 0x2, 0x7, 0x7, 0x6, 0x6, 0x2, 0x2, 0x2, };
//const unsigned char spriteLeft[]  PROGMEM = { 0x8, 0x8, 0x2, 0x2, 0x2, 0x6, 0x6, 0x7, 0x7, 0x2, };

#define SHIP_HORIZ_ACCELERATION 25
#define SHIP_MAX_SPEED 200
#define SHIP_HORIZ_DECELERATION 5

#define FLAG_FACING_RIGHT 0x4
#define FLAG_EXPLODING 0x8
#define FLAG_HIDDEN 0x10

PlayerShip::PlayerShip() : MovingGameObject()
{
	worldPos.x = worldPos.y = 0;
	setFlag(&flags, FLAG_FACING_RIGHT);
}

void PlayerShip::update()
{
	if(isFlagSet(flags, FLAG_EXPLODING))
	{ 
		explodingUpdate();
	}
	else
	{
		activeUpdate();
	}
	
}

void PlayerShip::activeUpdate()
{
	MovingGameObject::update();

	if (arduboy.pressed(UP_BUTTON) && worldPos.y > -HALF_SCREEN_HEIGHT)
	{
		worldPos.y--;
	}
	else if (arduboy.pressed(DOWN_BUTTON) && worldPos.y < HALF_SCREEN_HEIGHT - 3)
	{
		worldPos.y++;
	}

	if (arduboy.pressed(RIGHT_BUTTON))
	{
		if (!isFlagSet(flags, FLAG_FACING_RIGHT))
		{
			setFlag(&flags, FLAG_FACING_RIGHT);
		}
		velocity.x += SHIP_HORIZ_ACCELERATION;
		if (velocity.x > SHIP_MAX_SPEED)
		{
			velocity.x = SHIP_MAX_SPEED;
		}
	}
	else if (arduboy.pressed(LEFT_BUTTON))
	{
		if (isFlagSet(flags, FLAG_FACING_RIGHT))
		{
			unsetFlag(&flags, FLAG_FACING_RIGHT);
		}
		velocity.x -= SHIP_HORIZ_ACCELERATION;
		if (velocity.x < -SHIP_MAX_SPEED)
		{
			velocity.x = -SHIP_MAX_SPEED;
		}
	}
	else
	{
		if (velocity.x > 0)
		{
			velocity.x -= SHIP_HORIZ_DECELERATION;
			if (velocity.x < 0)
			{
				velocity.x = 0;
			}
		}
		else if (velocity.x < 0)
		{
			velocity.x += SHIP_HORIZ_DECELERATION;
			if (velocity.x > 0)
			{
				velocity.x = 0;
			}
		}
	}

	if (arduboy.justPressed(B_BUTTON))
	{
		fire();
	}

	if (arduboy.justPressed(A_BUTTON) && !arduboy.pressed(B_BUTTON))
	{
		pGameState->onSmartBomb();
	}
}

void PlayerShip::explodingUpdate() 
{
	explosionTimer--;
	if (explosionTimer == 0)
	{
		explode();
	}
	else if(explosionTimer % 4 == 0)
	{
		setFlag(&flags, FLAG_HIDDEN, !isFlagSet(flags, FLAG_HIDDEN));
	}
}

float PlayerShip::getCameraTarget()
{
	float cameraTarget;
	if (isFlagSet(flags, FLAG_FACING_RIGHT))
	{
		cameraTarget = (worldPos.x + 32) - (5 * (velocity.x/100.0));
		if (cameraTarget >= WORLD_WIDTH)
		{
			cameraTarget -= WORLD_WIDTH;
		}
	}
	else
	{
		cameraTarget = (worldPos.x - 32) - (5 * (velocity.x/100.0));

		if (cameraTarget < 0)
		{
			cameraTarget += WORLD_WIDTH;
		}
	}

	return cameraTarget;
}

void PlayerShip::fire()
{
	PlayerShot* shot = pGameState->getPlayerShot();
	if (shot != NULL)
	{
		shot->worldPos.y = worldPos.y+1;

		float shotVelocity;
		if (isFlagSet(flags, FLAG_FACING_RIGHT))
		{
			shot->worldPos.x = worldPos.x + 8;
			shotVelocity = velocity.x + 300;
		}
		else
		{
			shot->worldPos.x = worldPos.x - 1;
			shotVelocity = velocity.x - 300;

		}

		shot->setActive(true);
		shot->fire(shotVelocity);
	}
}

void PlayerShip::render(Vector2Int screenPos)
{
	if (!isFlagSet(flags, FLAG_HIDDEN))
	{
		renderSprite(spriteRight, screenPos, isFlagSet(flags, FLAG_FACING_RIGHT) ? MIRROR_NONE : MIRROR_HORIZONTAL);
	}
}

void PlayerShip::destroy()
{
	if (!isFlagSet(flags, FLAG_EXPLODING))
	{
		pGameState->freezeActors();
		setFlag(&flags, FLAG_EXPLODING);
		explosionTimer = 30;
	}
}

Rect PlayerShip::getCollisionRect()
{
	return Rect(worldPos.x, worldPos.y, 8, 3);
}


void PlayerShip::setActive(bool active)
{
	GameObject::setActive(active);

	if (active)
	{
		unsetFlag(&flags, FLAG_EXPLODING);
		unsetFlag(&flags, FLAG_HIDDEN);
		setFlag(&flags, FLAG_FACING_RIGHT);
		velocity.x = velocity.y = 0;
	}
}

void PlayerShip::explode()
{
	explodeObject(&flags, worldPos, PARTICLES_PLAYER);
	pGameState->addToScore(25);

	// Destroy any carried humans
	for (uint8_t i = 0; i < TOTAL_HUMANOIDS; i++)
	{
		Humanoid* pHumanoid = pGameState->getHumanoid(i);
		if (pHumanoid->isActive() && pHumanoid->isCarried())
		{
			pHumanoid->destroy();
		}
	}
}

bool PlayerShip::isExploding()
{
	return isFlagSet(flags, FLAG_EXPLODING);
}

bool PlayerShip::facingRight()
{
	return isFlagSet(flags, FLAG_FACING_RIGHT);
}

void PlayerShip::cancelExplosion()
{
	unsetFlag(&flags, FLAG_EXPLODING);
}
