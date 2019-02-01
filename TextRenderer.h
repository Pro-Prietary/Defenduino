#include "Renderer.h"

#ifndef   TEXTRENDERER_H
#define   TEXTRENDERER_H
class TextRenderer : public Renderer
{
public:
	TextRenderer();
	TextRenderer(const __FlashStringHelper* text);
	virtual void render(Vector2Int screenPos);
	void setText(const __FlashStringHelper* text);

private:
	const __FlashStringHelper* text;
};
#endif