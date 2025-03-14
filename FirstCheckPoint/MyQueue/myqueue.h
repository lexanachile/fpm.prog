#pragma once
using namespace std;

template<typename T>
class myq {
    class myNode {
    public:
        T info;
        myNode *next = nullptr;
    };

    myNode *head = nullptr;
    myNode *tail = nullptr;

public:
    myq() { head = tail = nullptr; }

    myq(const myq &x) {
        myNode *buf = x.head;
        while (buf != nullptr) {
            push(buf->info);
            buf = buf->next;
        }
    }

    myq(myq &&x) {
        head = x.head;
        tail = x.tail;
        x.head = nullptr;
        x.tail = nullptr;
    }

    ~myq() {
        myNode *buf;
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
            myNode *buf = new myNode;
            buf->info = x;
            tail->next = buf;
            tail = buf;
        }
    }

    void pop() {
        myNode *buf = head;
        head = head->next;
        T ret = buf->info;
        delete buf;
    }

    T front() {
        if (head != nullptr) throw "Empty queue";
        else {
            return head->info;
        }
    }

    T back() {
        if (tail == nullptr) throw "Empty queue";
        else {
            return tail->info;
        }
    }

    void show() {
        myNode *buf = head;
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

    int size() {
        if (head == nullptr) return 0;
        int capacity = 1;
        myNode *buf = head;
        while (buf->next != nullptr) {
            capacity++;
            buf = buf->next;
        }
        return capacity;
    }

    void clear() {
        myNode *buf;
        while (head != nullptr) {
            buf = head;
            head = head->next;
            delete buf;
        }
    }

    void swap(myq &x) {
        myq temp = *this;
        *this = x;
        x = temp;
    }

    void emplace(int pos, T x) {
        if (pos > size() - 1) push(x);
        else {
            myNode *buf = head;
            for (int i = 0; i < pos - 1; i++) {
                buf = buf->next;
            }
            myNode *temp = new myNode;
            temp->info = x;
            temp->next = buf->next;
            buf->next = temp;
        }
    }

    myq &operator=(const myq &x) {
        myNode *buf;
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

    myq &operator=(myq &&x) {
        if (this == &x) return *this;
        head = x.head;
        tail = x.tail;
        x.head = nullptr;
        x.tail = nullptr;
        return *this;
    }
};
