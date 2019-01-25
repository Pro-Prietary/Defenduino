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
