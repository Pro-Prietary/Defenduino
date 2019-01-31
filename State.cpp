#include "State.h"
#include "Globals.h"
#include <Arduboy2.h>


State::State(Camera* pCamera)
{
	pCameraObject = pCamera;
}

void State::addObject(GameObject* obj)
{
  if(pHeadObject==NULL)
  {
    pHeadObject = obj;
  }

  pTailObject->pNextSibling = obj;
  obj->pPrevSibling = pTailObject;
  pTailObject = obj;
}

void State::update()
{
	GameObject* pNextObj = pHeadObject;
	while(pNextObj!=NULL)
	{
		pHeadObject->update();
		pNextObj = pHeadObject->pNextSibling;
	}

	pCameraObject->update();
	pCameraObject->render(pHeadObject);
}

