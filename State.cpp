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
		pNextObj->update();
		pNextObj = pNextObj->pNextSibling;
	}

	pCameraObject->update();
	pCameraObject->render(pHeadObject);
}

Camera* State::getCamera()
{
	return pCameraObject;
}
