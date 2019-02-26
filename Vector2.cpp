#include "Vector2.h"
#include <math.h>

Vector2::Vector2() {}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2 Vector2::operator-(const Vector2& in) 
{
	return Vector2(x - in.x, y - in.y);
}

float Vector2::magnitude()
{
	return sqrt(x*x + y*y);
}

Vector2 Vector2::normalize()
{
	float m = magnitude();
	if (m > 0) 
	{
		return Vector2(x / m, y / m);
	}
	else
	{
		return Vector2(x, y);
	}
}