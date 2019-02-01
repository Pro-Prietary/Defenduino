#include "TextObject.h"

TextObject::TextObject(const __FlashStringHelper* text)
{
	TextObject();
	setText(text);
}

TextObject::TextObject() : GameObject()
{
	pRenderer = &renderer;
}

void TextObject::setText(const __FlashStringHelper* text)
{
	renderer.setText(text);
}