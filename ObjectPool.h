#pragma once
#include "GameObject.h"

class ObjectPool
{
public:
	void pool(GameObject* obj);
	GameObject* get();

private:
	GameObject * pHead = NULL;
};