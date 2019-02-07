#include "ObjectPool.h"

void ObjectPool::pool(GameObject* pObj)
{
#ifdef _DEBUG
	Serial.print(F("Adding to pool.  New object: "));
	Serial.print((int)pObj);
	Serial.print(F(" Current tail: "));
	Serial.println((int)pTail);
#endif

	pObj->pPrevSibling = pTail;

	if (pTail != NULL)
	{
		pTail->pNextSibling = pObj;
	}

	pTail = pObj;

#ifdef _DEBUG
	Serial.print(F("New tail after add: "));
	Serial.println((int)pTail);
#endif
}

GameObject* ObjectPool::get()
{
	GameObject* obj = NULL;
#ifdef _DEBUG
	Serial.print(F("Getting object from pool.  Current tail: "));
	Serial.println((int)pTail);
#endif

	if (pTail != NULL)
	{
		obj = pTail;
		if (obj->pPrevSibling != NULL)
		{
			obj->pPrevSibling->pNextSibling = NULL;
			pTail = obj->pPrevSibling;
		}
		else
		{
			pTail = NULL;
		}
		obj->pPrevSibling = obj->pNextSibling = NULL;
	}

#ifdef _DEBUG
	Serial.print(F("Tail after get: "));
	Serial.println((int)pTail);
#endif

	return obj;
}