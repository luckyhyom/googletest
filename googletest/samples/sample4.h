#ifndef GOOGLETEST_SAMPLES_SAMPLE4_H_
#define GOOGLETEST_SAMPLES_SAMPLE4_H_

// 단순한 단조 증가 카운터 클래스 (Monotonic Counter).
class Counter {
 private:
  int counter_;  // 카운터 값

 public:
  // 0부터 시작하는 카운터를 생성한다.
  Counter() : counter_(0) {}

  // 현재 카운터 값을 반환하고, 값을 증가시킨다.
  int Increment();

  // 현재 카운터 값을 반환하고, 값을 감소시킨다.
  int Decrement();

  // 현재 카운터 값을 표준 출력(STDOUT)에 출력한다.
  void Print() const;
};

#endif  // GOOGLETEST_SAMPLES_SAMPLE4_H_
