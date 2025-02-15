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
1. 각 테스트에서 재사용할 수 있는 변수나 함수를 설정할 수 있는 기능
2. 각 테스트는 `SetUp()`에서 초기 상태를 자동으로 설정하여 독립적인 환경을 갖춘 후 실행

### 주의
각 테스트에서 초기 값이 어떻게 설정되었는지 볼 수 없다면 (매번 픽스쳐에 정의된 선언을 봐야한다면) 이해하기 어려울 수 있다. 각 테스트의 맥락 파악에 불필요하지만 반복적인 설정을 해야하는 상황에서 쓸모있어보임

뭐든 Trade-off 이므로, 읽기 쉬운 쪽으로 작성할 것.

간단한 변수의 경우 테스트 안에서 직접 선언하는 것이 이해하기 쉬울 확률이 높음