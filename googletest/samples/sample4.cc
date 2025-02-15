#include "sample4.h"

#include <stdio.h>

// 현재 카운터 값을 반환하고, 값을 증가시킨다.
int Counter::Increment() { return counter_++; }

// 현재 카운터 값을 반환하고, 값을 감소시킨다.
// 카운터 값이 0보다 작아질 수 없으며, 이 경우 0을 반환한다.
int Counter::Decrement() {
  if (counter_ == 0) {
    return counter_;
  } else {
    return counter_--;
  }
}

// 현재 카운터 값을 표준 출력(STDOUT)에 출력한다.
void Counter::Print() const { printf("%d", counter_); }
