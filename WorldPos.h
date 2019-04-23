#pragma once

struct WorldPos
{
public:
	float x = 0;

	WorldPos();
	WorldPos(float x, float y);
	WorldPos operator-(const WorldPos& in);

	float magnitude();
	WorldPos normalize();
	float getY();
	void setY(float Y);

private:
	int y = 0;
};
