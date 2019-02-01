#include "GameObject.h"
#include "Vector2.h"
#include "Vector2Int.h"

#ifndef   CAMERA_H
#define   CAMERA_H
class Camera : public GameObject
{
  public:
    void render(GameObject* pFirstObj);

private:
	virtual Vector2Int worldToScreenPos(Vector2 worldPos);
};
#endif

