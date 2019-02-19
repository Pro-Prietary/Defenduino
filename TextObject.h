#pragma once

#include "GameObject.h"

class TextObject : public GameObject
{
public:
	TextObject(const __FlashStringHelper* text);
	TextObject();
	void setText(const __FlashStringHelper* text);
	void render(Vector2Int screenPos);

private:
	const __FlashStringHelper* text;

};
