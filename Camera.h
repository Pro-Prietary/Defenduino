#pragma once

#include "MovingGameObject.h"
#include "Vector2.h"
#include "Vector2Int.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define HALF_SCREEN_WIDTH 64
#define HALF_SCREEN_HEIGHT 32

class Camera : public MovingGameObject
{
  public:
    void render(GameObject* pFirstObj);

private:
	virtual Vector2Int worldToScreenPos(Vector2 worldPos);
};


