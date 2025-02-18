#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Cat.h"
#include "CatFood.h"

/**
 * 1. Food의 반환 값에 따른 Cat의 포만감 변화 여부 (검증)
 * 2. Food의 메서드 호출 여부 (검증)
 * 3. Food의 메서드 호출 순서 (검증)
 * 4. Food의 메서드 호출 시 입력된 인자 (검증)
 * 5. Food의 메서드 반환 값 (조작)
 * 6. DI 없이 Cat 메서드에서 직접 호출하는 함수 Mocking
 */

class MockCatFood : public ICatFood {
  public:
    MOCK_METHOD(bool, IsEmpty, (), (override));
    MOCK_METHOD(int, Burn,(), (override));
};

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::NiceMock;

TEST(CatTest, EatFood) {
  NiceMock<MockCatFood> food;
  bool isEmpty = false;
  int energy = 10;

  EXPECT_CALL(food, IsEmpty())
    .Times(1)
    .WillOnce(Return(isEmpty));

  EXPECT_CALL(food, Burn())
    .Times(1)
    .WillOnce(Return(energy));

  Cat cat;
  cat.Eat(food);
}

