#include "Camera.h"
#include <Arduboy2.h>

#ifndef   STATE_H
#define   STATE_H
class State
{

public:
	virtual void update();
protected:
	State();

};
#endif