#include <Arduboy2.h>

#ifndef   RENDERER_H
#define   RENDERER_H
class Renderer
{
public:
	virtual void render(int16_t cameraX, int16_t cameraY, int16_t objectX, int16_t objectY);
};
#endif