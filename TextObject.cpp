#include "TextObject.h"

TextObject::TextObject(const __FlashStringHelper* text)
{
	TextObject();
	setText(text);
}

TextObject::TextObject() : GameObject()
{
}

void TextObject::setText(const __FlashStringHelper* text)
{
	renderer.setText(text);
}

void TextObject::render(Vector2Int screenPos)
{
	renderer.render(screenPos);
}
