#include "Camera.h"
#include <Arduboy2.h>

#ifndef   STATE_H
#define   STATE_H
class State
{

public:
	void addObject(GameObject* pObj);
	Camera* getCamera();
	virtual void update();
	void removeObject(GameObject* pObj);
protected:
	State(Camera* pCameraObject);

private:
  GameObject* pHeadObject = NULL;
  GameObject* pTailObject = NULL;
  Camera* pCameraObject = NULL;
};
#endif