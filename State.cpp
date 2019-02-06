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
#ifdef _DEBUG
	  Serial.println("Adding new head object");
#endif
    pHeadObject = obj;
	pTailObject = obj;
  }
  else
  {
#ifdef _DEBUG
	  Serial.println("Adding new sibling object");
#endif

	  pTailObject->pNextSibling = obj;
	  obj->pPrevSibling = pTailObject;
	  pTailObject = obj;
  }
}

void State::update()
{
	GameObject* pNextObj = pHeadObject;
	while(pNextObj!=NULL)
	{
		// Get next first in case it changes in the process.
		GameObject* thisObj = pNextObj;
		pNextObj = pNextObj->pNextSibling;

		thisObj->update();
	}

	pCameraObject->update();
	pCameraObject->render(pHeadObject);
}

Camera* State::getCamera()
{
	return pCameraObject;
}
