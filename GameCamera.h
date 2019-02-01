#include "Camera.h"

class GameCamera : public Camera
{
public:
	GameCamera();
	virtual Vector2Int worldToScreenPos(Vector2 worldPos);
	virtual void update();

private:
	int leftEdge;
	int rightEdge;
	int topEdge;
	int bottomEdge;
};