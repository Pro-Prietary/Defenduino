class GameObject
{
  public:
    virtual void update();
    GameObject* pNextSibling = 0l;
    GameObject* pPrevSibling = 0l;

  private:  
    GameObject();
};

