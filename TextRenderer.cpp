#include "TextRenderer.h"

TextRenderer::TextRenderer()
{
}

TextRenderer::TextRenderer(const __FlashStringHelper* text)
{
	this->text = text;
}