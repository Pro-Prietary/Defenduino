#include <Arduboy2.h>

class GameObject
{
  public:
    virtual void update();
    GameObject* pNextSibling = NULL;
    GameObject* pPrevSibling = NULL;

  protected:  
    GameObject();
    int16_t x;
    int16_t y;
};

