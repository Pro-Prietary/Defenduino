#include "WorldPos.h"
#include <math.h>

WorldPos::WorldPos() {}

WorldPos::WorldPos(float x, float y)
{
	this->x = x;

	// Because bounds of y are quite small, can be an int at 2 points of precision
	this->y = y * 100;
}

WorldPos WorldPos::operator-(const WorldPos& in)
{
	return WorldPos(x - in.x, getY() - in.getY());
}

float WorldPos::magnitude()
{
	float y = getY();
	return sqrt(x*x + y*y);
}

WorldPos WorldPos::normalize()
{
	float m = magnitude();
	if (m > 0) 
	{
		return WorldPos(x / m, getY() / m);
	}
	else
	{
		return WorldPos(x, getY());
	}
}

float WorldPos::getY()
{
	return (float)y / 100.0;
}

void WorldPos::setY(float newY)
{
	y = newY * 100;
}