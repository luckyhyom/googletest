#include "sample4.h"

#include "gtest/gtest.h"

namespace {
// Increment() 메서드를 테스트한다.

TEST(Counter, Increment) {
  Counter c;

  // 카운터 값이 0일 때, Decrement()가 0을 반환하는지 확인한다.
  EXPECT_EQ(0, c.Decrement());

  // EXPECT_EQ()는 인수를 정확히 한 번만 평가하므로,
  // 함수 호출로 인해 부작용(side effect)이 발생할 수 있다.

  EXPECT_EQ(0, c.Increment()); // 초기 값이 0이므로 0을 반환 후 1로 증가
  EXPECT_EQ(1, c.Increment()); // 1을 반환 후 2로 증가
  EXPECT_EQ(2, c.Increment()); // 2를 반환 후 3으로 증가

  EXPECT_EQ(3, c.Decrement()); // 3을 반환 후 2로 감소
}

}  // namespace
