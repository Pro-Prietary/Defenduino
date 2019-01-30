#include "Renderer.h"

class TextRenderer : public Renderer
{
public:
	TextRenderer();
	TextRenderer(const __FlashStringHelper* text);
	virtual void render(int16_t cameraX, int16_t cameraY, int16_t objectX, int16_t objectY);


private:
	const __FlashStringHelper* text;
};