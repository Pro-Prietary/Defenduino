class GameObject
{
  public:
    virtual void update();
    GameObject* nextSibling = 0l;

  private:  
    GameObject();
};

