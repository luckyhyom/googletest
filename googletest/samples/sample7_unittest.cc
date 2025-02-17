/**
  📌 PrimeTable 인터페이스를 구현하는 여러 개의 클래스를 하나의 테스트 케이스에서 검증
  📌 OnTheFlyPrimeTable, PreCalculatedPrimeTable<1000>을 테스트
  📌 객체 생성을 팩토리 함수(CreatePrimeTableFunc)로 추상화
  📌 Value-Parameterized Test를 사용하여 같은 테스트를 다양한 구현체에 대해 실행
 */

// This sample shows how to test common properties of multiple
// implementations of an interface (aka interface tests) using
// value-parameterized tests. Each test in the test case has
// a parameter that is an interface pointer to an implementation
// tested.

// The interface and its implementations are in this header.
#include "prime_tables.h"
#include "gtest/gtest.h"
namespace {

using ::testing::TestWithParam;
using ::testing::Values;

// As a general rule, to prevent a test from affecting the tests that come
// after it, you should create and destroy the tested objects for each test
// instead of reusing them.  In this sample we will define a simple factory
// function for PrimeTable objects.  We will instantiate objects in test's
// SetUp() method and delete them in TearDown() method.
/**
  📌 각 테스트에서 new와 delete를 반복해야 함 → 메모리 관리가 번거로움
  📌 테스트 코드가 객체 생성 방법에 의존적 → 객체 생성 방식이 바뀌면 모든 테스트를 수정해야 함
 */
typedef PrimeTable* CreatePrimeTableFunc();

PrimeTable* CreateOnTheFlyPrimeTable() { return new OnTheFlyPrimeTable(); }

template <size_t max_precalculated>
PrimeTable* CreatePreCalculatedPrimeTable() {
  return new PreCalculatedPrimeTable(max_precalculated);
}

// Inside the test body, fixture constructor, SetUp(), and TearDown() you
// can refer to the test parameter by GetParam().  In this case, the test
// parameter is a factory function which we call in fixture's SetUp() to
// create and store an instance of PrimeTable.
/**
  📌 TestWithParam<CreatePrimeTableFunc*>를 상속
  📌 GetParam()을 호출하면 팩토리 함수 포인터(CreatePrimeTableFunc*)를 얻을 수 있음
  📌 SetUp()에서 팩토리 함수를 호출해 table_을 생성
  📌 TearDown()에서 객체를 삭제하여 메모리 누수 방지
 */
class PrimeTableTestSmpl7 : public TestWithParam<CreatePrimeTableFunc*> {
 public:
  ~PrimeTableTestSmpl7() override { delete table_; }
  void SetUp() override { table_ = (*GetParam())(); }
  void TearDown() override {
    delete table_;
    table_ = nullptr;
  }

 protected:
  PrimeTable* table_;
};

TEST_P(PrimeTableTestSmpl7, ReturnsFalseForNonPrimes) {
  EXPECT_FALSE(table_->IsPrime(-5));
  EXPECT_FALSE(table_->IsPrime(0));
  EXPECT_FALSE(table_->IsPrime(1));
  EXPECT_FALSE(table_->IsPrime(4));
  EXPECT_FALSE(table_->IsPrime(6));
  EXPECT_FALSE(table_->IsPrime(100));
}

TEST_P(PrimeTableTestSmpl7, ReturnsTrueForPrimes) {
  EXPECT_TRUE(table_->IsPrime(2));
  EXPECT_TRUE(table_->IsPrime(3));
  EXPECT_TRUE(table_->IsPrime(5));
  EXPECT_TRUE(table_->IsPrime(7));
  EXPECT_TRUE(table_->IsPrime(11));
  EXPECT_TRUE(table_->IsPrime(131));
}

TEST_P(PrimeTableTestSmpl7, CanGetNextPrime) {
  EXPECT_EQ(2, table_->GetNextPrime(0));
  EXPECT_EQ(3, table_->GetNextPrime(2));
  EXPECT_EQ(5, table_->GetNextPrime(3));
  EXPECT_EQ(7, table_->GetNextPrime(5));
  EXPECT_EQ(11, table_->GetNextPrime(7));
  EXPECT_EQ(131, table_->GetNextPrime(128));
}

// In order to run value-parameterized tests, you need to instantiate them,
// or bind them to a list of values which will be used as test parameters.
// You can instantiate them in a different translation module, or even
// instantiate them several times.
//
// Here, we instantiate our tests with a list of two PrimeTable object
// factory functions:
INSTANTIATE_TEST_SUITE_P(OnTheFlyAndPreCalculated, PrimeTableTestSmpl7,
                         Values(&CreateOnTheFlyPrimeTable,
                                &CreatePreCalculatedPrimeTable<1000>));

}  // namespace
