// 이 파일은 PrimeTable 인터페이스를 정의하며,
// 해당 인터페이스를 구현하는 클래스를 포함하고 있습니다.
// 이 인터페이스는 숫자가 소수인지 판별하고,
// 주어진 숫자보다 큰 다음 소수를 찾는 기능을 제공합니다.
// 이 인터페이스는 Google Test의 매개변수화된 테스트(Parameterized Test) 예제에서 사용됩니다.

#ifndef GOOGLETEST_SAMPLES_PRIME_TABLES_H_
#define GOOGLETEST_SAMPLES_PRIME_TABLES_H_

#include <algorithm>

// PrimeTable 인터페이스 정의
class PrimeTable {
 public:
  virtual ~PrimeTable() = default;

  // 숫자 n이 소수인지 여부를 반환한다.
  virtual bool IsPrime(int n) const = 0;

  // 주어진 숫자 p보다 큰 가장 작은 소수를 반환한다.
  // 단, 가능한 소수의 범위를 초과하면 -1을 반환한다.
  virtual int GetNextPrime(int p) const = 0;
};

// 구현 방법 #1: 소수를 **실시간으로 계산(On-the-fly)** 하는 클래스
class OnTheFlyPrimeTable : public PrimeTable {
 public:
  bool IsPrime(int n) const override {
    if (n <= 1) return false;

    for (int i = 2; i * i <= n; i++) {
      // n이 1과 자기 자신을 제외한 다른 수로 나누어지면 소수가 아니다.
      if ((n % i) == 0) return false;
    }

    return true;
  }

  int GetNextPrime(int p) const override {
    if (p < 0) return -1;

    for (int n = p + 1;; n++) {
      if (IsPrime(n)) return n;
    }
  }
};

// 구현 방법 #2: **소수를 미리 계산하여 배열에 저장**하는 클래스
class PreCalculatedPrimeTable : public PrimeTable {
 public:
  // 'max'는 이 테이블에서 저장할 최대 숫자를 지정한다.
  explicit PreCalculatedPrimeTable(int max)
      : is_prime_size_(std::max(1, max + 1)),
        is_prime_(new bool[static_cast<size_t>(is_prime_size_)]) {
    CalculatePrimesUpTo(is_prime_size_ - 1);
  }

  ~PreCalculatedPrimeTable() override { delete[] is_prime_; }

  // 숫자 n이 소수인지 여부를 확인한다.
  bool IsPrime(int n) const override {
    return 0 <= n && n < is_prime_size_ && is_prime_[n];
  }

  // 주어진 숫자 p보다 큰 가장 작은 소수를 반환한다.
  int GetNextPrime(int p) const override {
    for (int n = p + 1; n < is_prime_size_; n++) {
      if (is_prime_[n]) return n;
    }
    return -1;
  }

 private:
  // 주어진 최대 값까지의 소수를 계산하여 배열에 저장한다.
  void CalculatePrimesUpTo(int max) {
    ::std::fill(is_prime_, is_prime_ + is_prime_size_, true);
    is_prime_[0] = is_prime_[1] = false;

    // 모든 가능한 소수를 검사한다. (2는 유일한 짝수 소수)
    for (int i = 2; i * i <= max; i += i % 2 + 1) {
      if (!is_prime_[i]) continue;

      // i의 배수를 모두 소수가 아닌 것으로 표시한다.
      // 이미 더 작은 배수들은 이전 루프에서 확인되었으므로, i의 제곱부터 시작한다.
      for (int j = i * i; j <= max; j += i) {
        is_prime_[j] = false;
      }
    }
  }

  const int is_prime_size_;  // 배열 크기
  bool* const is_prime_;      // 소수 여부를 저장하는 배열

  // 컴파일러 경고 "대입 연산자를 자동으로 생성할 수 없음"을 방지하기 위해 
  // 대입 연산자를 비활성화한다.
  void operator=(const PreCalculatedPrimeTable& rhs);
};

#endif  // GOOGLETEST_SAMPLES_PRIME_TABLES_H_
