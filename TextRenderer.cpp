#include "TextRenderer.h"
#include "Globals.h"


TextRenderer::TextRenderer()
{
}

TextRenderer::TextRenderer(const __FlashStringHelper* text)
{
	setText(text);
}

void TextRenderer::setText(const __FlashStringHelper* text)
{
	this->text = text;
}

void TextRenderer::render(int16_t cameraX, int16_t cameraY, int16_t objectX, int16_t objectY)
{
	if (text != NULL)
	{
		arduboy.print(text);
	}
}