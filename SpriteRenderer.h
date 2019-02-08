#pragma once

#include "Renderer.h"

class SpriteRenderer : public Renderer
{
public:
	SpriteRenderer();
	virtual void render(Vector2Int screenPos);
	void setSpriteData(unsigned char newSprite[], byte width, byte height);

private:
	unsigned char* spriteData;
	byte width;
	byte height;
	byte halfWidth;
};