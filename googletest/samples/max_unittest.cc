#include "gtest/gtest.h"

// 최대값 찾기 함수
template <typename T>
T Max(T a, T b) {
  return (a > b) ? a : b;
}

// 테스트 픽스처 정의
template <typename T>
class MaxFunctionTest : public testing::Test {};

using testing::Types;
typedef Types<int, double, float> MaxTypes;
TYPED_TEST_SUITE(MaxFunctionTest, MaxTypes);

// 최대값 테스트
TYPED_TEST(MaxFunctionTest, ReturnsLargerValue) {
  EXPECT_EQ(Max<TypeParam>(10, 20), 20);
  EXPECT_EQ(Max<TypeParam>(-5, -10), -5);
}
