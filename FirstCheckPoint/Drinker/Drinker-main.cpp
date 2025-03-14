#include <iostream>
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
  // friend istream& operator>>(istream& in, myq& x);
  // friend ostream& operator<<(ostream& in, myq& x);
};


int main() {
  myq<int> first;
  myq<int> second;
  int a, b;
  for (int i = 0; i < 5; i++) {
      cin >> a;
    first.push(a);
  }
  for (int i = 0; i < 5; i++) {
    cin >> b;
    second.push(b);
  }
  double k = 0;
  while ((!first.isempty() && !second.isempty()) && k != 1000000) {
    a = first.pop();
    b = second.pop();
    if ((a == 9 && b == 0 || b > a) && (a != 0 || b != 9)) {
      second.push(a);
      second.push(b);
    }
      else {
      first.push(a);
      first.push(b);

    }
    k++;
  }
  if (k == 1000000)
    cout << "botva";
  else if (first.isempty())
      cout << "second " << k;
    else cout << "first " << k;
  return 0;
  }