#include "Camera.h"
#include <Arduboy2.h>

class State
{

public:
  virtual void update();
  void addObject(GameObject* obj);

private:
  GameObject* pHeadObject = NULL;
  GameObject* pTailObject = NULL;
  Camera* pCameraObject = NULL;
};
