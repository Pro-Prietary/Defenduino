#pragma once
#include "GameObject.h"

class Landscape : public GameObject
{
public:
	virtual void render(Vector2Int screenPos);

private:
	Vector2Int translatePoint(Vector2Int screenPos, Vector2Int point);
	bool translatedPointIsVisible(int point);

};