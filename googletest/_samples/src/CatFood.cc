#include "CatFood.h"

CatFood::CatFood(int energy, int amount) : energy(energy), amount(amount) {}

bool CatFood::IsEmpty() {
  return this->amount > 0 ? true : false;
}

int CatFood::Burn() {
  this->amount--;
  return this->energy;
}