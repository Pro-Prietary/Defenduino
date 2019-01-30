#include "GameObject.h"

class Camera : public GameObject
{
  public:
    void render(GameObject* pFirstObj);
};

