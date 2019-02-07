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
	  Serial.print(F("Adding sibling to scene.  New object: "));
	  Serial.print((int)obj);
	  Serial.print(F(" Current tail: "));
	  Serial.println((int)pTailObject);
#endif


	  pTailObject->pNextSibling = obj;
	  obj->pPrevSibling = pTailObject;
	  pTailObject = obj;

#ifdef _DEBUG
	  Serial.print(F("New scene tail after add: "));
	  Serial.println((int)pTailObject);
#endif
  }
}

void State::removeObject(GameObject* pObj)
{
	if (pObj == pHeadObject)
	{
		Serial.println((int)pObj->pNextSibling);
		pHeadObject = pObj->pNextSibling;
	}
	else if (pObj == pTailObject)
	{
		Serial.println((int)pObj->pPrevSibling);
		pTailObject = pObj->pPrevSibling;
	}

	if (pObj->pNextSibling != NULL)
	{
		pObj->pNextSibling->pPrevSibling = pObj->pPrevSibling;
	}

	if (pObj->pPrevSibling != NULL)
	{
		pObj->pPrevSibling->pNextSibling = pObj->pNextSibling;
	}
	pObj->pNextSibling = NULL;
	pObj->pPrevSibling = NULL;
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
