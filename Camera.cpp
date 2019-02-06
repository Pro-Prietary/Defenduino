#include "Camera.h"
#include "Globals.h"

void Camera::render(GameObject* pFirstObj)
{
	GameObject* pNextObj = pFirstObj;
	while (pNextObj != NULL)
	{
		// Get next first in case it changes in the process.
		GameObject* pCurrentObj = pNextObj;
		pNextObj = pNextObj->pNextSibling;

		Vector2Int screenPos = worldToScreenPos(pCurrentObj->worldPos);
		pCurrentObj->render(screenPos);
	}
}

/*
* Static version.  Just casts floats to ints
*/
Vector2Int Camera::worldToScreenPos(Vector2 objPos)
{
	Vector2Int screenPos;
	screenPos.x = (int)objPos.x;
	screenPos.y = (int)objPos.y;
	return screenPos;
}


