#include "Camera.h"
#include "Globals.h"

void Camera::render(GameObject* pFirstObj)
{
	GameObject* pCurrentObj = pFirstObj;
	while (pCurrentObj != NULL)
	{
		Vector2Int screenPos = worldToScreenPos(pCurrentObj->worldPos);
		pCurrentObj->render(screenPos);
		pCurrentObj = pCurrentObj->pNextSibling;
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


