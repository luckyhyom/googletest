/**
 * 1. 여러 개의 테스트가 공통으로 사용하는 초기화 코드(SetUp)와 정리 코드(TearDown)를 하나의 클래스로 묶는 방법.
 * 2. 개별 테스트에서 중복되는 초기화 코드 작성을 피하고, 테스트를 독립적으로 실행할 수 있도록 도와줌.
 * 3. Google Test에서는 TEST_F(테스트픽스처, 테스트명) 형식으로 테스트를 정의함.
 * 
 * 테스트는 독립적이고 반복 가능해야 한다.
 */

// Google C++ 테스트 프레임워크를 사용하는 샘플 프로그램입니다.

// 이 예제에서는 Google Test의 고급 기능 중 하나인 "테스트 픽스처(Test Fixture)"를 사용합니다.
//
// 테스트 픽스처는 모든 테스트에서 공통적으로 사용하는 **객체 및 함수를 보관하는 공간**입니다.
// 테스트 픽스처를 사용하면 개별 테스트마다 동일한 초기화 및 정리 코드를 중복 작성할 필요가 없습니다.
// 또한, 테스트에서 자주 호출해야 하는 **서브 루틴(보조 함수)**을 정의하는 데 유용합니다.
//
// <기술적인 세부사항>
//
// 테스트는 **코드를 공유하지만, 데이터를 공유하지 않습니다.**
// 각 테스트는 **테스트 픽스처의 새로운 복사본을 개별적으로 제공받습니다.**
// 따라서 한 테스트에서 변경한 데이터가 다른 테스트로 전달되지 않으며, 이는 바람직하지 않은 방식입니다.
//
// 이러한 설계의 이유는 **테스트가 독립적이고 반복 가능해야 하기 때문**입니다.
// 즉, 한 테스트의 실패가 다른 테스트의 결과에 영향을 미쳐서는 안 됩니다.
// 만약 한 테스트가 다른 테스트의 출력을 필요로 한다면, 두 테스트는 하나의 큰 테스트로 합쳐져야 합니다.
//
// 또한, Google Test에서 제공하는 `EXPECT_TRUE`, `FAIL` 등의 매크로는 현재 실행 중인 테스트를 식별할 수 있어야 합니다.
// (Google Test는 테스트 결과를 출력할 때 각 실패가 어떤 테스트에서 발생했는지를 알려줍니다.)
// 이러한 매크로는 기본적으로 `Test` 클래스의 멤버 함수를 호출하는 방식으로 동작하기 때문에,
// **글로벌 함수에서는 사용할 수 없습니다.**  
// 따라서 테스트 서브 루틴(보조 함수)은 **테스트 픽스처 내부에서 정의해야 합니다.**
//
// </기술적인 세부사항>

#include "sample3-inl.h"
#include "gtest/gtest.h"
namespace {

// 테스트 픽스처를 사용하려면, `testing::Test` 클래스를 상속받아야 합니다.
class QueueTestSmpl3 : public testing::Test {
 protected:
  // `SetUp()`은 각 테스트가 실행되기 전에 호출됩니다.
  // 필요한 변수 초기화 작업이 있다면 여기서 수행하면 됩니다.
  // 만약 필요하지 않다면 생략할 수도 있습니다.
  void SetUp() override {
    q1_.Enqueue(1);
    q2_.Enqueue(2);
    q2_.Enqueue(3);
  }

  // `TearDown()`은 각 테스트가 실행된 후 호출됩니다.
  // 정리 작업이 필요할 경우 정의하면 되고, 필요 없으면 생략할 수 있습니다.
  //
  // virtual void TearDown() {
  // }

  // 몇몇 테스트에서 사용할 보조 함수(Helper function)입니다.
  static int Double(int n) { return 2 * n; }

  // `Queue::Map()` 함수를 테스트하기 위한 보조 함수입니다.
  void MapTester(const Queue<int>* q) {
    // 기존 큐(q)의 각 요소를 두 배로 만든 새로운 큐를 생성합니다.
    const Queue<int>* const new_q = q->Map(Double);

    // 새로운 큐의 크기가 기존 큐와 동일한지 확인합니다.
    ASSERT_EQ(q->Size(), new_q->Size());

    // 기존 큐와 새 큐의 요소가 기대한 대로 두 배 차이가 나는지 검증합니다.
    for (const QueueNode<int>* n1 = q->Head(), *n2 = new_q->Head();
         n1 != nullptr; n1 = n1->next(), n2 = n2->next()) {
      EXPECT_EQ(2 * n1->element(), n2->element());
    }

    // 할당된 새 큐를 삭제합니다.
    delete new_q;
  }

  // 테스트에서 사용할 변수들을 선언합니다.
  Queue<int> q0_;  // 빈 큐
  Queue<int> q1_;  // 1개의 요소(1) 포함
  Queue<int> q2_;  // 2개의 요소(2, 3) 포함
};

// `TEST_F`를 사용하여 테스트를 정의합니다.
// (`TEST_F`는 "테스트 픽스처"를 사용할 때 `TEST` 대신 사용합니다.)

// 기본 생성자 테스트
TEST_F(QueueTestSmpl3, DefaultConstructor) {
  // 테스트 픽스처에서 초기화된 데이터를 사용할 수 있습니다.
  EXPECT_EQ(0u, q0_.Size());  // q0_은 빈 큐이므로 크기가 0이어야 함
}

// `Dequeue()` 테스트
TEST_F(QueueTestSmpl3, Dequeue) {
  int* n = q0_.Dequeue();
  EXPECT_TRUE(n == nullptr);  // 빈 큐에서 `Dequeue()` 호출 시 nullptr을 반환해야 함

  n = q1_.Dequeue();
  ASSERT_TRUE(n != nullptr);
  EXPECT_EQ(1, *n);  // `q1_`에서 첫 번째 요소(1) 가져오기
  EXPECT_EQ(0u, q1_.Size());  // 제거 후 크기는 0이어야 함
  delete n;  // `Dequeue()`가 동적으로 할당한 메모리를 해제해야 함

  n = q2_.Dequeue();
  ASSERT_TRUE(n != nullptr);
  EXPECT_EQ(2, *n);  // `q2_`에서 첫 번째 요소(2) 가져오기
  EXPECT_EQ(1u, q2_.Size());  // 제거 후 크기는 1이어야 함
  delete n;  // 메모리 해제
}

// `Queue::Map()` 함수 테스트
TEST_F(QueueTestSmpl3, Map) {
  MapTester(&q0_);  // 빈 큐 테스트
  MapTester(&q1_);  // 요소 1개 큐 테스트
  MapTester(&q2_);  // 요소 2개 큐 테스트
}

}  // namespace
