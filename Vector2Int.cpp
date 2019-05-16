#include "Vector2Int.h"
#include "Globals.h"
#include <math.h>

Vector2Int::Vector2Int() {}

Vector2Int::Vector2Int(int x, int y)
{
	this->x = x;
	this->y = y;
}

Vector2Int Vector2Int::operator-(const Vector2Int& in)
{
	return Vector2Int(x - in.x, y - in.y);
}

float Vector2Int::magnitude()
{
	return sqrt((x*x) + (y*y));
}

Vector2Int Vector2Int::normalize()
{
	int m = magnitude();

	if (m != 0) 
	{
		return Vector2Int(x / m, y / m);
	}
	else
	{
		return Vector2Int(x, y);
	}
}

int Vector2Int::getPixelX()
{
	return x / 10;
}

int Vector2Int::getPixelY()
{
	return y / 10;
}