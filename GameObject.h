#include <Arduboy2.h>
#include "Renderer.h"

#ifndef   GAMEOBJECT_H
#define   GAMEOBJECT_H
class GameObject
{
public:
	virtual void update();
	virtual void render(int16_t cameraX, int16_t cameraY);
	GameObject* pNextSibling = NULL;
	GameObject* pPrevSibling = NULL;

protected:
	GameObject();
	Renderer* pRenderer;
	int16_t x;
	int16_t y;
}; 
#endif


