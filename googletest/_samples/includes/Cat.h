#include <iostream>
#include "CatFood.h"
class Cat {
  public:
    void Eat(ICatFood& food);
    std::string Say();
  private:
    void GetAngry();
    int satiety = 0;
};