#include "ObjectPool.h"

void ObjectPool::pool(GameObject* pObj)
{
	pObj->pNextSibling = pHead;
	pHead = pObj;
}

GameObject* ObjectPool::get()
{
	GameObject* obj = NULL;

	if (pHead != NULL)
	{
		obj = pHead;
		pHead = obj->pNextSibling;
		obj->pNextSibling = NULL;
	}

	return obj;
}