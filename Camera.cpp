#include "Camera.h"

void Camera::render(GameObject* pFirstObj)
{
	GameObject* pCurrentObj = pFirstObj;
	while (pCurrentObj != NULL)
	{
		pCurrentObj->render(x, y);
		pCurrentObj = pCurrentObj->pNextSibling;
	}
}

