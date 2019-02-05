#pragma once
#include "GameObject.h"

class LandscapeSegment : public GameObject
{
public:
	void setData(byte* newPoints, int totalNewCoords);
	virtual void render(Vector2Int screenPos);

private:
	Vector2Int translatePoint(Vector2Int screenPos, byte pointX, byte pointY);
	bool translatedPointIsVisible(int point);
	byte* points;
	int totalCoords;

};