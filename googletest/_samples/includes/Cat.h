#include "CatFood.h"

class Cat {
  public:
    void Eat(ICatFood& food);
    void GetAngry();
  private:
    int satiety = 0;
};