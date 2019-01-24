#include "GameObject.h"

class State
{

public:
  virtual void update();

private:
  GameObject* headObject = 0l;
};
