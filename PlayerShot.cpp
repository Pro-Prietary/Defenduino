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
#ifdef _DEBUG
		Serial.println(F("Drawing shot line"));
#endif
		arduboy.drawLine(screenPos.x, screenPos.y, screenPos.x - length, screenPos.y);
	}
}

void PlayerShot::fire(bool right)
{
	length = 1;

	if (right)
	{
		velocity.x = 1;
	}
	else
	{
		velocity.x = -1;
	}
}

void PlayerShot::update()
{
#ifdef _DEBUG
	Serial.println(F("PlayerShot::update"));
#endif
	GameObject::update();
	length++;
}
