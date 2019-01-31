#include "GameObject.h"

#ifndef   CAMERA_H
#define   CAMERA_H
class Camera : public GameObject
{
  public:
    void render(GameObject* pFirstObj);
};
#endif

