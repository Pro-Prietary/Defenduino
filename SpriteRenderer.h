#pragma once

#include "Renderer.h"

class SpriteRenderer : public Renderer
{
public:
	SpriteRenderer();
	virtual void render(Vector2Int screenPos);
	void setSpriteData(unsigned char newSprite[], int width, int height);

private:
	unsigned char* spriteData;
	int width;
	int height;
	int halfWidth;
};