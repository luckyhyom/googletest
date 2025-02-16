#include "gtest/gtest.h"
#include <memory>
#include "adder.h"

TEST(AdderTest, Add) {
  OnlineAdder adder;
  LocalAdder adder2;
  EXPECT_EQ(3, adder.add(1, 2));
  EXPECT_EQ(3, adder2.add(1, 2));
}

/**
 * Adder로 구현체를 추상화하여 선언하기 위해서 팩토리 함수 or 포인터를 사용한다.
 */
template <typename T>
class EveryAdderTest : public testing::Test {
  protected:
    void SetUp() override {
      adder = std::make_unique<T>();  // ✅ C++14 이상에서는 가능 (T가 Adder의 자식 클래스라면 자동 변환됨)
      // adder = std::unique_ptr<Adder>(std::make_unique<T>().release());  // ✅
       adder = std::move(std::make_unique<T>());  // ✅
    }
    std::unique_ptr<Adder> adder;
};

using testing::Types;

typedef Types<LocalAdder, OnlineAdder> Impls;

TYPED_TEST_SUITE(EveryAdderTest, Impls);

TYPED_TEST(EveryAdderTest, Add) {
  EXPECT_EQ(this->adder->add(1, 2), 3);
}