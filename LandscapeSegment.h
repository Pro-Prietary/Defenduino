#pragma once
#include "GameObject.h"

class LandscapeSegment : public GameObject
{
public:
	LandscapeSegment();
	void setData(byte* newPoints);
	void render(Vector2Int screenPos);

private:
	Vector2Int translatePoint(Vector2Int screenPos, byte pointX, byte pointY);
	bool translatedPointIsVisible(int point);
	byte* points;
	byte totalCoords;

};