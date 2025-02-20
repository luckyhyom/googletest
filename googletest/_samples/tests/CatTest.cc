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

/**
 * 1. Food의 반환 값에 따른 Cat의 포만감 변화 여부 (검증) ✅
 * 2. Food의 메서드 호출 여부 (검증) ❌
 * 3. Food의 메서드 호출 순서 (검증) ❌
 * 4. Food의 메서드 호출 시 입력된 인자 (검증) ❌
 * 5. Food의 메서드 반환 값 (조작) ❌
 * 6. DI 없이 Cat 메서드에서 직접 호출하는 함수 Mocking
 * 
 * [private 메서드는 간접 검증한다.]
 * GetAngry 호출 여부는 Cat의 해당 메서드를 오버라이드하여 Mocking 해야한다.
 * 하지만, 보통 private 메서드인 GetAngry는 아래의 방법을 통해 간접 테스트를 한다.
 * (1)GetAngry에서 사용되는 외부 함수를 Mocking
 * (2)GetAngry메서드가 상태를 수정한다면, 해당 상태가 영향을 주는 다른 public 메서드를 검증한다.
 */
TEST(CatTest, EatFoodSuccess) {
  bool isEmpty = false;
  int energy = 10;
  std::string said = "Maw~";

  /**
   * #2 여기서 Food의 메서드 호출 여부는 검증 대상이 아니다. (Times 매크로 필요 X)
   * #5 Food의 메서드 반환 값 (조작)
   */
  NiceMock<MockCatFood> food;
  EXPECT_CALL(food, IsEmpty())
    .WillOnce(Return(isEmpty));
  EXPECT_CALL(food, Burn())
    .WillOnce(Return(energy));

  // #1 Food의 반환 값에 따른 Cat의 포만감 변화 여부 (검증) ✅
  Cat cat;
  cat.Eat(food);
  EXPECT_EQ(cat.Say(), said);
}

TEST(CatTest, EatFoodFail) {
  bool isEmpty = true;
  int energy = 10;
  std::string said = "Maw!!";

  NiceMock<MockCatFood> food;
  EXPECT_CALL(food, IsEmpty())
    .WillOnce(Return(isEmpty));

  // #1 Food의 반환 값에 따른 Cat의 포만감 변화 여부 (검증) ✅
  Cat cat;
  cat.Eat(food);
  EXPECT_EQ(cat.Say(), said);
}

