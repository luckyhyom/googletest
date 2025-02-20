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
  // 집사가 사료를 주는 함수를 호출 (의존성 주입 없이 직접 호출 한다.)
  //int calorie = Feed();
  //this->satiety += calorie;
}

std::string Cat::Say() {
  if(satiety) {
    return "Maw~";
  } else {
    return "Maw!!";
  }
}