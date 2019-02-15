#pragma once

#include "GameObject.h"
#include "TextRenderer.h"

class TextObject : public GameObject
{
public:
	TextObject(const __FlashStringHelper* text);
	TextObject();
	void setText(const __FlashStringHelper* text);
	virtual void render(Vector2Int screenPos);

private:
	TextRenderer renderer;
};
