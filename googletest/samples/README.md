### How to Build Sample Unit Test

Check 1
option(BUILD_GMOCK "Builds the googlemock subproject" OFF)

Check 2
option(gtest_build_samples "Build gtest's sample programs." ON)


```
git clone https://github.com/google/googletest.git
cd googletest
mkdir build
cd build
cmake ..
make
```

# Test Fixture
1. 각 테스트에서 공통적으로 사용할 변수나 함수를 초기화한다
2. 각 테스트가 실행되기 전 `SetUp()`에서 초기 상태를 자동으로 설정한다.

### 주의
각 테스트에서 초기 값이 어떻게 설정되었는지 볼 수 없다면 (매번 픽스쳐에 정의된 선언을 봐야한다면) 이해하기 어려울 수 있다. 각 테스트의 맥락 파악에 불필요하지만 반복적인 설정을 해야하는 상황에서 쓸모있어보임

뭐든 Trade-off 이므로, 읽기 쉬운 쪽으로 작성할 것.

간단한 변수의 경우 테스트 안에서 직접 선언하는 것이 이해하기 쉬울 확률이 높음

# Super Fixture
1. Test Fixture를 만들때 상속을 활용하는 방법
2. 아래의 코드는 어떤 기능을 테스트 하든 5초 안에 종료되어야 한다는 조건이 있을 경우 상속받아 활용할 수 있다.

```cpp
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
```