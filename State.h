#include "Camera.h"
#include <Arduboy2.h>

class State
{

public:
	void addObject(GameObject* obj);
	virtual void update();

protected:
	State(Camera* pCameraObject);

private:
  GameObject* pHeadObject = NULL;
  GameObject* pTailObject = NULL;
  Camera* pCameraObject = NULL;
};
