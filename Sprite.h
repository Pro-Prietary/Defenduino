#pragma once

#include "GameObject.h"

class Sprite
{
public:
	Sprite();
	bool render(Vector2Int screenPos);

protected:
	void setSpriteData(unsigned char newSprite[], byte width, byte height);

private:
	unsigned char* spriteData;
	byte width;
	byte height;
	byte halfWidth;
};