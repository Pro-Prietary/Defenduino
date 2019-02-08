#include "State.h"
#include "Globals.h"
#include <Arduboy2.h>


State::State(Camera* pCamera)
{
	pCameraObject = pCamera;
}

void State::addObject(GameObject* pObj)
{
	pObj->pNextSibling = pHeadObject;
	pHeadObject = pObj;
}

void State::removeObject(GameObject* pObj, GameObject* pPrevObject)
{
	if (pObj == pHeadObject)
	{
		pHeadObject = pObj->pNextSibling;
	}
	else if(pPrevObject != NULL)
	{
		pPrevObject->pNextSibling = pObj->pNextSibling;
	}

	pObj->pNextSibling = NULL;
}

void State::update()
{
	GameObject* pNextObj = pHeadObject;
	GameObject* pPrevObj = NULL;
	while(pNextObj!=NULL)
	{
		// Get next first in case it changes in the process.
		GameObject* thisObj = pNextObj;
		pNextObj = pNextObj->pNextSibling;

		thisObj->update(pPrevObj);
		pPrevObj = thisObj;
	}

	pCameraObject->update(NULL);
	pCameraObject->render(pHeadObject);
}

Camera* State::getCamera()
{
	return pCameraObject;
}
