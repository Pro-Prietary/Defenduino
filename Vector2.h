#pragma once

struct Vector2
{
public:
	float x = 0;
	float y = 0;

	Vector2();
	Vector2(float x, float y);
	Vector2 operator-(const Vector2& in);

	float magnitude();
	Vector2 normalize();

};
