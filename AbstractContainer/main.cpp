#include <iostream>
#include <list>
#include <stack>

class AbstractContainer {
public:
    virtual ~AbstractContainer() {};
    virtual bool IsEmpty() const = 0;		    // контейнер пуст
    virtual bool IsFull()  const = 0;		    // контейнер полный
};

class AbstractStack: public AbstractContainer {
public:
    virtual void push(const int& n) = 0;		// втолкнуть в стек
    virtual void pop(int& n)  = 0;		    	// вытолкнуть из стека
};

class ArrayStack: public AbstractStack {
protected:
    int size, top;
    int *M;
public:
    ArrayStack(int size = 16) {
        M = new int[size];
       top = -1;
}
    ~ArrayStack() {
        delete[] M;
}
    void push(const int& n);		// втолкнуть в стек
    void pop(int& n);			// вытолкнуть из стека
    bool IsEmpty() const;
    bool IsFull() const ;
    friend class ArrayStackIterator;

};

class ListStack: public AbstractStack {

};

class AbstractQueue: public AbstractContainer {
public:
    virtual void push(const int& n) = 0;	    // втолкнуть в очередь
    virtual void del(int& n) = 0;			    // удалить из очереди
};



int main() {

    return 0;
}