// Copyright 2005, Google Inc.
// 모든 권리 보유.
//
// 소스 코드 및 바이너리 형태로 수정 여부와 관계없이 재배포 및 사용이 허용됩니다.
// 단, 다음 조건을 충족해야 합니다:
//
//     * 소스 코드 재배포 시 위의 저작권 공지, 이 조건 목록, 그리고 아래 면책 조항을 유지해야 합니다.
//     * 바이너리 형태로 재배포할 경우, 배포 문서 또는 기타 자료에 위의 저작권 공지, 이 조건 목록, 
//       그리고 아래 면책 조항을 포함해야 합니다.
//     * Google Inc.의 이름이나 기여자의 이름을 사용하여 파생 제품을 홍보하거나 보증할 수 없습니다.
//
// 이 소프트웨어는 "있는 그대로(AS IS)" 제공되며, 명시적이거나 암시적인 어떠한 보증도 없습니다. 
// 여기에는 상품성 및 특정 목적에 대한 적합성에 대한 암시적 보증도 포함됩니다.
// 저작권 소유자 또는 기여자는 소프트웨어 사용으로 인해 발생하는 
// 직접적, 간접적, 부수적, 특수적, 징벌적 또는 결과적 손해(예: 대체 상품 또는 서비스 조달, 
// 사용 손실, 데이터 손실, 이익 손실, 업무 중단 등)에 대해 어떠한 책임도 지지 않습니다.
// 이는 계약, 엄격한 책임, 불법 행위(과실 포함) 등의 법적 이론에 따라 발생한 손해에도 적용됩니다.
// 이러한 손해 발생 가능성을 사전에 인지했는지 여부와 관계없이 면책됩니다.

// Google C++ 테스트 프레임워크를 사용하는 샘플 프로그램.

#ifndef GOOGLETEST_SAMPLES_SAMPLE3_INL_H_
#define GOOGLETEST_SAMPLES_SAMPLE3_INL_H_

#include <stddef.h>

// Queue는 단일 연결 리스트(Singly Linked List)로 구현된 간단한 큐입니다.
//
// 요소 타입(E)은 반드시 복사 생성자를 지원해야 합니다.
template <typename E>  // E는 요소 타입
class Queue;

// QueueNode는 Queue의 노드이며, 요소(E)와 다음 노드를 가리키는 포인터를 포함합니다.
template <typename E>  // E는 요소 타입
class QueueNode {
  friend class Queue<E>;

 public:
  // 이 노드에 저장된 요소를 가져옵니다.
  const E& element() const { return element_; }

  // 큐에서 다음 노드를 가져옵니다.
  QueueNode* next() { return next_; }
  const QueueNode* next() const { return next_; }

 private:
  // 주어진 요소 값을 가진 노드를 생성합니다. next 포인터는 NULL로 설정됩니다.
  explicit QueueNode(const E& an_element)
      : element_(an_element), next_(nullptr) {}

  // 기본 대입 연산자 및 복사 생성자를 비활성화합니다.
  const QueueNode& operator=(const QueueNode&);
  QueueNode(const QueueNode&);

  E element_;        // 노드가 저장하는 요소
  QueueNode* next_;  // 다음 노드를 가리키는 포인터
};

template <typename E>  // E는 요소 타입
class Queue {
 public:
  // 빈 큐를 생성합니다.
  Queue() : head_(nullptr), last_(nullptr), size_(0) {}

  // 소멸자. 큐를 비웁니다.
  ~Queue() { Clear(); }

  // 큐를 비웁니다.
  void Clear() {
    if (size_ > 0) {
      // 1. 모든 노드를 삭제합니다.
      QueueNode<E>* node = head_;
      QueueNode<E>* next = node->next();
      for (;;) {
        delete node;
        node = next;
        if (node == nullptr) break;
        next = node->next();
      }

      // 2. 멤버 변수를 초기화합니다.
      head_ = last_ = nullptr;
      size_ = 0;
    }
  }

  // 요소 개수를 반환합니다.
  size_t Size() const { return size_; }

  // 큐의 첫 번째 요소를 가져옵니다. 큐가 비어 있으면 NULL을 반환합니다.
  QueueNode<E>* Head() { return head_; }
  const QueueNode<E>* Head() const { return head_; }

  // 큐의 마지막 요소를 가져옵니다. 큐가 비어 있으면 NULL을 반환합니다.
  QueueNode<E>* Last() { return last_; }
  const QueueNode<E>* Last() const { return last_; }

  // 큐의 끝에 요소를 추가합니다.
  // 요소의 복사본이 생성되며, 큐에 저장됩니다.
  // 큐에 저장된 요소를 변경해도 원본 객체에는 영향을 주지 않습니다.
  void Enqueue(const E& element) {
    QueueNode<E>* new_node = new QueueNode<E>(element);

    if (size_ == 0) {
      head_ = last_ = new_node;
      size_ = 1;
    } else {
      last_->next_ = new_node;
      last_ = new_node;
      size_++;
    }
  }

  // 큐의 첫 번째 요소를 제거하고 반환합니다. 큐가 비어 있으면 NULL을 반환합니다.
  E* Dequeue() {
    if (size_ == 0) {
      return nullptr;
    }

    const QueueNode<E>* const old_head = head_;
    head_ = head_->next_;
    size_--;
    if (size_ == 0) {
      last_ = nullptr;
    }

    E* element = new E(old_head->element());
    delete old_head;

    return element;
  }

  // 큐의 각 요소에 함수 또는 펑터(Functor)를 적용하고,
  // 결과를 새로운 큐로 반환합니다. 기존 큐는 변경되지 않습니다.
  template <typename F>
  Queue* Map(F function) const {
    Queue* new_queue = new Queue();
    for (const QueueNode<E>* node = head_; node != nullptr;
         node = node->next_) {
      new_queue->Enqueue(function(node->element()));
    }

    return new_queue;
  }

 private:
  QueueNode<E>* head_;  // 큐의 첫 번째 노드
  QueueNode<E>* last_;  // 큐의 마지막 노드
  size_t size_;         // 큐에 저장된 요소 개수

  // 큐의 복사를 금지합니다.
  Queue(const Queue&);
  const Queue& operator=(const Queue&);
};

#endif  // GOOGLETEST_SAMPLES_SAMPLE3_INL_H_
