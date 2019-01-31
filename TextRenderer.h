#include "Renderer.h"

#ifndef   TEXTRENDERER_H
#define   TEXTRENDERER_H
class TextRenderer : public Renderer
{
public:
	TextRenderer();
	TextRenderer(const __FlashStringHelper* text);
	virtual void render(int16_t cameraX, int16_t cameraY, int16_t objectX, int16_t objectY);
	void setText(const __FlashStringHelper* text);

private:
	const __FlashStringHelper* text;
};
#endif