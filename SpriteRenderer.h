#pragma once

#include "Renderer.h"

class SpriteRenderer : public Renderer
{
public:
	SpriteRenderer();
	virtual void render(Vector2Int screenPos);
	void setSpriteData(unsigned char newSprite[]);

private:
	unsigned char* spriteData;

};