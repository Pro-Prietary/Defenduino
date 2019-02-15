#include "Camera.h"
#include <Arduboy2.h>

#ifndef   STATE_H
#define   STATE_H
class State
{

public:
	Camera* getCamera();
	virtual void update();
protected:
	State(Camera* pCameraObject);

private:
  Camera* pCameraObject = NULL;
};
#endif