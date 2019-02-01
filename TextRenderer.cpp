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

void TextRenderer::render(Vector2Int screenPos)
{
	if (text != NULL)
	{
		arduboy.setCursor(screenPos.x, screenPos.y);
		arduboy.print(text);
	}
}