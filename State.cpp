#include "State.h"
#include <Arduboy2.h>

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
  if(pNextObj!=NULL)
  {
    pHeadObject->update();
    pNextObj = pHeadObject->pNextSibling;
  }

  pCameraObject->update();
  pCameraObject->render(pHeadObject);
}

