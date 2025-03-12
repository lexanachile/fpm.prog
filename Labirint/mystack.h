#pragma once
using namespace std;
template <typename T>
class mystack {
	struct myNode {
    T info;
    myNode* next;
  };
  myNode* head;
 public:
     mystack() { 
         head = nullptr;
     }
     ~mystack() {
       myNode* buf;
       while (head != nullptr) {
         buf = head;
         head = head->next;
         delete buf;
       }
     }
     mystack(const mystack& x) { 
         myNode* buf;
       mystack<T> y;
       buf = x.head;
       while (buf != nullptr) {
         y.push(buf->info);
         buf = buf->next;
       }
       buf = y.head;
       while (buf != nullptr) {
         push(buf->info);
         buf = buf->next;
       }
     }
     mystack(mystack&& x) { 
         head = x.head;
       x.head = nullptr;
     }

     mystack& operator=(mystack&& x) { 
         if (this == &x) return *this;
         head = x.head;
         x.head = nullptr;
         return *this;
     }

     void push(T x) { 
         if (head == nullptr) {
         head = new myNode{x, nullptr};
         } else {
           myNode* buf = new myNode;
           buf->info = x;
           buf->next = head;
           head = buf;         
         }
  }
     T pop() { 
           T ret = head->info;
           myNode* buf = head;
           head = head->next;
           delete buf;
         return ret;
     }
     int isempty() { 
         if (head == nullptr)
         return 1;
       else
         return 0;
     }

     mystack& operator=(mystack& x) {
       myNode* buf;
       while (head != nullptr) {
         buf = head;
         head = head->next;
         delete buf;
       }
       mystack<T> y;
       buf = x.head;
       while (buf != nullptr) {
         y.push(buf->info);
         buf = buf->next;
       }
       buf = y.head;
       while (buf != nullptr) {
         push(buf->info);
         buf = buf->next;
       }
       return *this;
     }

     void show() {
         myNode* buf = head;
       while (buf != nullptr) {
           cout << buf->info << endl;
         buf = buf->next;
       }
     }
};
