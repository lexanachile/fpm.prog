#pragma once
using namespace std;

template<typename T>
class mystack {
    struct myNode {
        T info;
        myNode *next;
    };

    myNode *head;

public:
    mystack() {
        head = nullptr;
    }

    ~mystack() {
        myNode *buf;
        while (head != nullptr) {
            buf = head;
            head = head->next;
            delete buf;
        }
    }

    mystack(const mystack &x) {
        myNode *buf;
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

    mystack(mystack &&x) {
        head = x.head;
        x.head = nullptr;
    }

    void push(const T &x) {
        if (head == nullptr) {
            head = new myNode{x, nullptr};
        } else {
            myNode *buf = new myNode;
            buf->info = x;
            buf->next = head;
            head = buf;
        }
    }

    void pop() {
        if (head != nullptr) {
            myNode *buf = head;
            head = head->next;
            delete buf;
        }
    }

    T top() {
        if (head == nullptr) throw "Empty stack";
        return head->info;
    }

    int isempty() {
        if (head == nullptr)
            return 1;
        else
            return 0;
    }

    mystack &operator=(mystack &x) {
        myNode *buf;
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

    mystack &operator=(mystack &&x) {
        if (this == &x) return *this;
        head = x.head;
        x.head = nullptr;
        return *this;
    }

    void show() {
        myNode *buf = head;
        while (buf != nullptr) {
            cout << buf->info << endl;
            buf = buf->next;
        }
    }

    int size() {
        myNode *buf = head;
        int count = 0;
        while (buf != nullptr) {
            count++;
            buf = buf->next;
        }
        delete buf;
        return count;
    }
    void clear() {
        while (head != nullptr) {
            myNode *buf = head;
            head = head->next;
            delete buf;
        }
    }
    void swap(mystack &x) {
        mystack buf = *this;
        *this = x;
        x = buf;
    }
    void emplace(int pos, T value) {
        int num = size();
        if (pos > num - 1) push(value);
        else {
            mystack temp;
            myNode *buf = head;
            while (buf != nullptr) {
                temp.push(buf->info);
                buf = buf->next;
            }
            clear();
            for (int i = 0; i < pos; ++i) {
                push(temp.top());
                temp.pop();
            }
            push(value);
            for (int i = 0; i < num - pos; ++i) {
                push(temp.top());
                temp.pop();
            }
        }
    }
    bool operator==(mystack &x) {
        int num = x.size();
        if (size() != num) return false;
        while (num != 0) {
            --num;
            myNode *a = head;
            myNode *b = x.head;
            if (a->info != b->info) return false;
            a = a->next;
            b = b->next;
        }
        return true;
    }
    bool operator!=(mystack &x) {
        int num = x.size();
        if (size() != num) return true;
        while (num != 0) {
            --num;
            myNode *a = head;
            myNode *b = x.head;
            if (a->info != b->info) return true;
            a = a->next;
            b = b->next;
        }
        return false;
    }
};
