#include "Landscape.h"
#include "Vector2Int.h"
#include "Camera.h"
#include "Globals.h"
#include <Arduboy2.h>

const Vector2Int points[] PROGMEM = { Vector2Int(0,45), Vector2Int(10,60), Vector2Int(100, 50), Vector2Int(150, 45),  Vector2Int(225, 51),  Vector2Int(300, 60),  
	Vector2Int(425, 44),  Vector2Int(525, 47), Vector2Int(610, 62), Vector2Int(650, 50), Vector2Int(725, 55), Vector2Int(840, 52), Vector2Int(890, 49)
	, Vector2Int(950, 60), Vector2Int(990, 54), Vector2Int(1000, 60) };
#define TOTAL_LANDSCAPE_POINTS 16

/// Screen pos is the relative screen position of the far left of the landscape
void Landscape::render(Vector2Int screenPos)
{
	//Serial.print("ScreenPos.x = ");
	//Serial.println(screenPos.x);
	// Iterate over each pair of points and draw lines if any point is visible based on screenPos
	Vector2Int translatedFirst = translatePoint(screenPos, points[0]);
	bool firstIsVisible = translatedPointIsVisible(translatedFirst.x);
	bool secondIsVisible = false;
	for (int i = 0; i < TOTAL_LANDSCAPE_POINTS-1; i++)
	{
		Vector2Int translatedSecond;
		if (i + 1 == TOTAL_LANDSCAPE_POINTS)
		{
			translatedSecond = translatePoint(screenPos, points[0]);
		}
		else
		{
			translatedSecond = translatePoint(screenPos, points[i+1]);
		}
		secondIsVisible = translatedPointIsVisible(translatedSecond.x);


		// If either is visible, draw
		if (firstIsVisible || secondIsVisible)
		{
			arduboy.drawLine(translatedFirst.x, translatedFirst.y, translatedSecond.x, translatedSecond.y, WHITE);
		}

		firstIsVisible = secondIsVisible;
		translatedFirst.x = translatedSecond.x;
		translatedFirst.y = translatedSecond.y;

	}
}

Vector2Int Landscape::translatePoint(Vector2Int screenPos, Vector2Int point)
{
	return Vector2Int(screenPos.x + point.x, point.y);
}

bool Landscape::translatedPointIsVisible(int point)
{
	return point >= 0 && point < SCREEN_WIDTH;
}