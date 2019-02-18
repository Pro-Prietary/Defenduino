#include "TextObject.h"
#include "Globals.h"

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
	this->text = text;
}

void TextObject::render(Vector2Int screenPos)
{
	if (text != NULL)
	{
		arduboy.setCursor(screenPos.x, screenPos.y);
		arduboy.print(text);
	}
}
