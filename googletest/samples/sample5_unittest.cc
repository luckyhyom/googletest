/**
 * Test Fixture - 상속을 활용하기
 * 
 * 아래 예제는 5초 안에 종료되어야 하는 기능을 위한 슈퍼 픽스처를 만든다.
 * 어떤 기능을 테스트 하던지 5초안에 종료되어야 하는 조건이 생기는 경우, 슈퍼 픽스처를 상속받는다.
 */

// 이 샘플은 테스트 픽스처(Test Fixture)를 여러 테스트 케이스에서 재사용하는 방법을 설명한다.
// 이를 위해 기존 테스트 픽스처에서 파생된 서브 픽스처를 정의한다.
//
// 테스트 픽스처를 정의할 때, 해당 픽스처를 사용할 테스트 케이스의 이름을 지정해야 한다.
// 따라서 하나의 테스트 픽스처는 단 하나의 테스트 케이스에서만 사용될 수 있다.
//
// 하지만, 여러 개의 테스트 케이스가 동일하거나 약간의 차이가 있는 테스트 픽스처를 사용할 필요가 있을 때가 있다.
// 예를 들어, GUI 라이브러리의 모든 테스트가 폰트나 브러시 같은 중요한 시스템 리소스를 낭비하지 않도록 확인하려고 할 수 있다.
// Google Test에서는 공통적인 로직을 "슈퍼 픽스처(Super Fixture, 즉 부모 클래스)"에 넣고,  
// 각 테스트 케이스가 이 슈퍼 픽스처를 상속받아 사용할 수 있도록 한다.

#include <limits.h>
#include <time.h>

#include "sample1.h"
#include "sample3-inl.h"
#include "gtest/gtest.h"

namespace {
// 이 샘플에서는 모든 테스트가 약 **5초 이내**에 완료되도록 보장해야 한다.
// 만약 테스트가 5초 이상 걸리면 실패한 것으로 간주한다.
//
// 테스트 시간을 측정하는 코드를 "QuickTest"라는 테스트 픽스처에 넣는다.
// QuickTest는 다른 테스트 픽스처들이 상속받아 사용할 **슈퍼 픽스처**로 설계되었기 때문에,
// "QuickTest"라는 이름을 가진 테스트 케이스는 존재하지 않는다. (이것은 정상적인 설계임)
//
// 이후, 여러 개의 테스트 픽스처가 QuickTest를 상속받아 사용하게 된다.
class QuickTest : public testing::Test {
 protected:
  // SetUp()은 각 테스트가 시작되기 직전에 실행된다.
  // 여기에서 테스트 시작 시간을 기록한다.
  void SetUp() override { start_time_ = time(nullptr); }

  // TearDown()은 각 테스트가 끝난 직후 호출된다.
  // 여기에서 테스트가 너무 오래 걸렸는지 확인한다.
  void TearDown() override {
    // 테스트가 종료된 시간을 가져온다.
    const time_t end_time = time(nullptr);

    // 테스트가 5초 이내에 완료되었는지 확인한다.
    // 참고: SetUp()과 TearDown()에서도 Google Test의 검증(assertion)을 사용할 수 있다.
    EXPECT_TRUE(end_time - start_time_ <= 5) << "테스트가 너무 오래 걸렸습니다.";
  }

  // 테스트 시작 시간 (UTC 초 단위)
  time_t start_time_;
};

// QuickTest를 상속받아 IntegerFunctionTest라는 테스트 픽스처를 만든다.
// 이 픽스처를 사용하는 모든 테스트는 자동으로 "빠르게 실행"되어야 한다.
class IntegerFunctionTest : public QuickTest {
  // QuickTest에서 이미 필요한 로직을 포함하고 있으므로
  // 추가적인 로직이 필요하지 않아 본문을 비워둔다.
};

// 이제 IntegerFunctionTest 테스트 케이스를 작성할 수 있다.

// Factorial() 함수 테스트
TEST_F(IntegerFunctionTest, Factorial) {
  // 음수 입력에 대한 팩토리얼 테스트
  EXPECT_EQ(1, Factorial(-5));
  EXPECT_EQ(1, Factorial(-1));
  EXPECT_GT(Factorial(-10), 0);

  // 0의 팩토리얼 테스트
  EXPECT_EQ(1, Factorial(0));

  // 양수 입력에 대한 팩토리얼 테스트
  EXPECT_EQ(1, Factorial(1));
  EXPECT_EQ(2, Factorial(2));
  EXPECT_EQ(6, Factorial(3));
  EXPECT_EQ(40320, Factorial(8));
}

// IsPrime() 함수 테스트
TEST_F(IntegerFunctionTest, IsPrime) {
  // 음수 입력 테스트
  EXPECT_FALSE(IsPrime(-1));
  EXPECT_FALSE(IsPrime(-2));
  EXPECT_FALSE(IsPrime(INT_MIN));

  // 기본적인 예제 테스트
  EXPECT_FALSE(IsPrime(0));
  EXPECT_FALSE(IsPrime(1));
  EXPECT_TRUE(IsPrime(2));
  EXPECT_TRUE(IsPrime(3));

  // 양수 입력 테스트
  EXPECT_FALSE(IsPrime(4));
  EXPECT_TRUE(IsPrime(5));
  EXPECT_FALSE(IsPrime(6));
  EXPECT_TRUE(IsPrime(23));
}

// 다음 테스트 케이스(QueueTest)도 "빠르게 실행"되어야 하므로,  
// QuickTest를 상속받아 또 다른 테스트 픽스처를 만든다.
//
// QueueTest 테스트 픽스처는 QuickTest의 기능을 그대로 상속받으며,  
// 추가적인 로직과 공유 객체를 포함한다.
// 새로운 내용은 테스트 픽스처 내부에서 추가로 정의한다.
class QueueTest : public QuickTest {
 protected:
  void SetUp() override {
    // 먼저 부모 클래스(QuickTest)의 SetUp()을 실행한다.
    QuickTest::SetUp();

    // 그리고 이 테스트 픽스처(QueueTest)에 필요한 추가적인 초기화를 수행한다.
    q1_.Enqueue(1);
    q2_.Enqueue(2);
    q2_.Enqueue(3);
  }

  // 기본적으로 TearDown()은 QuickTest::TearDown()의 동작을 그대로 상속받는다.
  // QueueTest에서 별도의 정리 작업이 필요하지 않으므로 생략한다.
  //
  // virtual void TearDown() {
  //   QuickTest::TearDown();
  // }

  Queue<int> q0_;
  Queue<int> q1_;
  Queue<int> q2_;
};

// 이제 QueueTest 픽스처를 사용한 테스트를 작성한다.

// 기본 생성자 테스트
TEST_F(QueueTest, DefaultConstructor) { EXPECT_EQ(0u, q0_.Size()); }

// Dequeue() 테스트
TEST_F(QueueTest, Dequeue) {
  int* n = q0_.Dequeue();
  EXPECT_TRUE(n == nullptr);  // 빈 큐에서 Dequeue() 호출 시 nullptr을 반환해야 함

  n = q1_.Dequeue();
  EXPECT_TRUE(n != nullptr);
  EXPECT_EQ(1, *n);  // q1에서 첫 번째 요소(1)를 가져옴
  EXPECT_EQ(0u, q1_.Size());  // 요소를 제거한 후 크기가 0인지 확인
  delete n;

  n = q2_.Dequeue();
  EXPECT_TRUE(n != nullptr);
  EXPECT_EQ(2, *n);  // q2에서 첫 번째 요소(2)를 가져옴
  EXPECT_EQ(1u, q2_.Size());  // 요소를 제거한 후 크기가 1인지 확인
  delete n;
}
}  // namespace

// 필요한 경우, 기존에 정의된 테스트 픽스처에서 또 다른 테스트 픽스처를 파생할 수도 있다.
// 예를 들어, QueueTest를 상속받는 새로운 픽스처를 만들 수도 있다.
// Google Test는 테스트 픽스처의 상속 깊이에 제한을 두지 않지만,
// 너무 깊어지면 코드가 복잡해질 수 있으므로 적절한 깊이를 유지하는 것이 좋다.
