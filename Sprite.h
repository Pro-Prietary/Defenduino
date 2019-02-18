#pragma once

#include "GameObject.h"

class Sprite
{
public:
	Sprite();
	void render(Vector2Int screenPos);
	bool isVisible();


protected:
	void setSpriteData(unsigned char newSprite[], byte width, byte height);

private:
	unsigned char* spriteData;
	byte width;
	byte height;
	byte halfWidth;
	bool bIsVisible;
};