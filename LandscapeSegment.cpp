#include "LandscapeSegment.h"
#include "Vector2Int.h"
#include "Camera.h"
#include "Globals.h"
#include <Arduboy2.h>

#define TOTAL_COORDINATES 8

LandscapeSegment::LandscapeSegment() : GameObject()
{
}

void LandscapeSegment::setData(byte* newPoints)
{
	points = newPoints;
}

/// Screen pos is the relative screen position of the far left of the landscape
void LandscapeSegment::render(Vector2Int screenPos)
{
	// If far from the camera, flip to the other side for wrapping
	if (screenPos.x < -HALF_WORLD_WIDTH)
	{
		screenPos.x += WORLD_WIDTH;
	}
	else if (screenPos.x > HALF_WORLD_WIDTH)
	{
		screenPos.x -= WORLD_WIDTH;
	}
 
	/*Serial.print("Total points in segment = ");
	Serial.println(totalPoints);*/
	// Iterate over each pair of points and draw lines if any point is visible based on screenPos
	Vector2Int translatedFirst = translatePoint(screenPos, pgm_read_byte(points), pgm_read_byte(points+1));
	bool firstIsVisible = translatedPointIsVisible(translatedFirst.x);
	bool secondIsVisible = false;
	for (int i = 2; i < TOTAL_COORDINATES; i+=2)
	{
		Vector2Int translatedSecond;
		translatedSecond = translatePoint(screenPos, pgm_read_byte(points+i), pgm_read_byte(points + i + 1));
		secondIsVisible = translatedPointIsVisible(translatedSecond.x);

		// If either is visible, draw
		if (firstIsVisible || secondIsVisible)
		{
			/*Serial.print("Drawing line.  start x = ");
			Serial.print(translatedFirst.x);
			Serial.print(" start y = ");
			Serial.print(translatedFirst.y);
			Serial.print(" end x = ");
			Serial.print(translatedSecond.x);
			Serial.print(" end y = ");
			Serial.println(translatedSecond.y);*/

			arduboy.drawLine(translatedFirst.x, translatedFirst.y, translatedSecond.x, translatedSecond.y, WHITE);
		}

		firstIsVisible = secondIsVisible;
		translatedFirst.x = translatedSecond.x;
		translatedFirst.y = translatedSecond.y;
	}
}

Vector2Int LandscapeSegment::translatePoint(Vector2Int screenPos, byte pointX, byte pointY)
{
	Vector2Int translated(screenPos.x + pointX, pointY);
	return translated;
}

bool LandscapeSegment::translatedPointIsVisible(int point)
{
	return point >= 0 && point < SCREEN_WIDTH;
}