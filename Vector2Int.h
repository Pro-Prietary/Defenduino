#pragma once

#include <Arduboy2.h>

struct Vector2Int
{
public:
	int x = 0;
	int y = 0;
	Vector2Int();
	Vector2Int(int newX, int newY);
};
