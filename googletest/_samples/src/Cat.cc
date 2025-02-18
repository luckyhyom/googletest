#pragma once  // 중복 포함 방지
#include "Cat.h"


void Cat::Eat(ICatFood& food) {
  if(food.IsEmpty()) {
    this->GetAngry();
    return;
  }

  int calorie = food.Burn();
  this->satiety += calorie;
}

void Cat::GetAngry() {
  // 집사를 호출하는 함수 호출 (의존성 주입 없이 직접 호출 한다.)
}