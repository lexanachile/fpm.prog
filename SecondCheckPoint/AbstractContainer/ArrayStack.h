#pragma once
#include "AbstractStack.h"
#include <iostream>
using namespace std;
class ArrayStack : public AbstractStack
{
protected:
    int size;
    int *M;
    int top;
public:
    ArrayStack(int _size = 16)
    {
        size = _size;
        M = new int[size];
        top = -1;
    }
    ArrayStack(const ArrayStack &s)
    {
        size = s.size;
        M = new int[size];
        top = s.top;
        for (int i = 0; i <= top; ++i)
        {
            M[i] = s.M[i];
        }
    }

    ~ArrayStack()
    {
        delete[] M;
    }
    void push(const int &n)
    {
        if (IsFull())
        {
            throw "stack is full";
        }
        M[top + 1] = n;
        top = top + 1;
    }
    void pop()
    {
        if (IsEmpty())
        {
            throw "stack is empty";
        }
        top = top - 1;
    }
    bool IsEmpty() const
    {
        return top == -1;
    }
    bool IsFull() const
    {
        return top == size - 1;
    }
    int Top() const
    {
        if (IsEmpty())
        {
            throw "stack is empty";
        }
        return M[top];
    }
    int Size() const
    {
        return top+1;
    }
    void Show() const
    {
        if (IsEmpty())
        {
            throw "stack is empty";
        }
        int i = top;
        while (i != -1)
        {
            cout << M[i] << " ";
            i--;
        }
        cout << endl;

    }
    friend class ArrayStackIterator;
};