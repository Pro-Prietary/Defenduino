#include "PlayerShip.h"
#include "Globals.h"

const unsigned char spriteRight[] PROGMEM = { 0x2, 0x7, 0x7, 0x6, 0x6, 0x2, 0x2, 0x2, };
const unsigned char spriteLeft[]  PROGMEM = { 0x2, 0x2, 0x2, 0x6, 0x6, 0x7, 0x7, 0x2, };

#define SHIP_HORIZ_ACCELERATION 0.25
#define SHIP_MAX_SPEED 2
#define SHIP_HORIZ_DECELERATION 0.15

PlayerShip::PlayerShip() : GameObject()
{
	renderer.setSpriteData(spriteRight, 8, 3);
	pRenderer = &renderer;
	worldPos.x = worldPos.y = 0;
}

void PlayerShip::update()
{
	GameObject::update();

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
		facingRight = true;
		renderer.setSpriteData(spriteRight, 8, 3);
		velocity.x += SHIP_HORIZ_ACCELERATION;
		if (velocity.x > SHIP_MAX_SPEED)
		{
			velocity.x = SHIP_MAX_SPEED;
		}
	}
	else if (arduboy.pressed(LEFT_BUTTON))
	{
		facingRight = false;
		renderer.setSpriteData(spriteLeft, 8, 3);
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
}

float PlayerShip::getCameraTarget()
{
	float cameraTarget;
	if (facingRight)
	{
		cameraTarget = (worldPos.x + 32) - (5 * velocity.x);
		if (cameraTarget >= WORLD_WIDTH)
		{
			cameraTarget -= WORLD_WIDTH;
		}
	}
	else
	{
		cameraTarget = (worldPos.x - 32) - (5 * velocity.x);

		if (cameraTarget < 0)
		{
			cameraTarget += WORLD_WIDTH;
		}
	}



	return cameraTarget;
}