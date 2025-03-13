#pragma once
using namespace std;

template <typename T>
class myq {
  class myNode {
   public:
    T info;
    myNode* next = nullptr;
  };
  myNode* head = nullptr;
  myNode* tail = nullptr;

 public:
  myq() { head = tail = nullptr; }
  myq(const myq& x) {
    myNode* buf = x.head;
    while (buf != nullptr) {
      push(buf->info);
      buf = buf->next;
    }
  }
  myq(myq&& x) { 
      head = x.head;
    tail = x.tail;
    x.head = nullptr;
    x.tail = nullptr;
  }
  ~myq() {
    myNode* buf;
    while (head != nullptr) {
      buf = head;
      head = head->next;
      delete buf;
    }
  }
  void push(T x) {
    if (head == nullptr) {
      head = new myNode;
      head->info = x;
      tail = head;
    } else {
      myNode* buf = new myNode;
      buf->info = x;
      tail->next = buf;
      tail = buf;
    }
  }
  T pop() {
    myNode* buf = head;
    head = head->next;
    T ret = buf->info;
    delete buf;
    return ret;
  }
  void show() {
    myNode* buf = head;
    while (buf != nullptr) {
      cout << buf->info << " ";
      buf = buf->next;
    }
    cout << endl;
  }
  int isempty() {
    if (head == nullptr)
      return 1;
    else
      return 0;
  }
  myq& operator=(const myq& x) {
    myNode* buf;
    while (head != nullptr) {
      buf = head;
      head = head->next;
      delete buf;
    }
    buf = x.head;
    while (buf != nullptr) {
      push(buf->info);
      buf = buf->next;
    }
    return *this;
  }

  myq& operator=(myq&& x) {
    if (this == &x) return *this;
    head = x.head;
    tail = x.tail;
    x.head = nullptr;
    x.tail = nullptr;
    return *this;
  }
};