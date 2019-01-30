#include "GameObject.h"
#include "TextRenderer.h"

class TextObject : public GameObject
{
public:
	TextObject(const __FlashStringHelper* text);

private:
	TextRenderer renderer;
};