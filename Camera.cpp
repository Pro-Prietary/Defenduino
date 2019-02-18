#include "Camera.h"
#include "Globals.h"

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


