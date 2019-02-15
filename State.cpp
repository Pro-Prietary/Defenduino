#include "State.h"
#include "Globals.h"
#include <Arduboy2.h>


State::State(Camera* pCamera)
{
	pCameraObject = pCamera;
}

void State::update()
{
}

Camera* State::getCamera()
{
	return pCameraObject;
}
