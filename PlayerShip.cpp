#include "PlayerShip.h"
#include "Globals.h"

const unsigned char spriteRight[] PROGMEM = { 0x2, 0x7, 0x7, 0x6, 0x6, 0x2, 0x2, 0x2, };
const unsigned char spriteLeft[]  PROGMEM = { 0x2, 0x2, 0x2, 0x6, 0x6, 0x7, 0x7, 0x2, };

#define SHIP_HORIZ_ACCELERATION 25
#define SHIP_MAX_SPEED 200
#define SHIP_HORIZ_DECELERATION 15

#define FLAG_FACING_RIGHT 0x4

PlayerShip::PlayerShip() : MovingGameObject()
{
	setSpriteData(spriteRight, 8, 3);
	worldPos.x = worldPos.y = 0;
	setFlag(FLAG_FACING_RIGHT);
}

void PlayerShip::update()
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
		if (!isFlagSet(FLAG_FACING_RIGHT))
		{
			setFlag(FLAG_FACING_RIGHT);
		}
		setSpriteData(spriteRight, 8, 3);
		velocity.x += SHIP_HORIZ_ACCELERATION;
		if (velocity.x > SHIP_MAX_SPEED)
		{
			velocity.x = SHIP_MAX_SPEED;
		}
	}
	else if (arduboy.pressed(LEFT_BUTTON))
	{
		if (isFlagSet(FLAG_FACING_RIGHT))
		{
			unsetFlag(FLAG_FACING_RIGHT);
		}
		setSpriteData(spriteLeft, 8, 3);
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
}

float PlayerShip::getCameraTarget()
{
	float cameraTarget;
	if (isFlagSet(FLAG_FACING_RIGHT))
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
	PlayerShot* shot = ((GameState*)(stateManager.getCurrentState()))->getPlayerShot();
	if (shot != NULL)
	{
		shot->worldPos.y = worldPos.y+1;

		float shotVelocity;
		if (isFlagSet(FLAG_FACING_RIGHT))
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
#ifdef _DEBUG
	else
	{
		Serial.println(F("Laser pool exhausted. Not firing."));
	}
#endif
}

void PlayerShip::render(Vector2Int screenPos)
{
	if (Sprite::render(screenPos))
	{
		setFlag(FLAG_VISIBLE);
	}
	else
	{
		unsetFlag(FLAG_VISIBLE);
	}
}