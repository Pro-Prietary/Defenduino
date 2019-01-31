#include "GameObject.h"
#include "TextRenderer.h"

#ifndef   TEXTOBJECT_H
#define   TEXTOBJECT_H
class TextObject : public GameObject
{
public:
	TextObject(const __FlashStringHelper* text);
	TextObject();
	void setText(const __FlashStringHelper* text);

private:
	TextRenderer renderer;
};
#endif