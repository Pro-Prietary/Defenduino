#include "PlayerShot.h"
#include "Globals.h"

void PlayerShot::render(Vector2Int screenPos)
{
	if (screenPos.x < 0 || screenPos.x >= SCREEN_WIDTH)
	{
#ifdef _DEBUG
		Serial.println(F("Pooling shot"));
#endif
		((GameState*)(stateManager.getCurrentState()))->pool(this);
	}
	else
	{
		arduboy.drawLine(screenPos.x, screenPos.y, screenPos.x - length, screenPos.y);
	}
}

void PlayerShot::fire(float xVelocity)
{
	length = 1;
	velocity.x = xVelocity;
}

void PlayerShot::update()
{
	GameObject::update();
	length++;
}
