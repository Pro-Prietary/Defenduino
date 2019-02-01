#pragma once

#include "Renderer.h"

class SpriteRenderer : public Renderer
{
public:
	SpriteRenderer();
	virtual void render(int16_t cameraX, int16_t cameraY, int16_t objectX, int16_t objectY);
	void setSpriteData(unsigned char newSprite[]);

private:
	unsigned char* spriteData;

};