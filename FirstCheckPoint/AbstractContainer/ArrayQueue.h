#pragma once
#include "AbstractQueue.h"
#include <iostream>
using namespace std;
class ArrayQueue : public AbstractQueue
{
protected:
    int size; // размерность массива
    int *p;	  // указатель на массив
    int head; // индекс первого занятого элемента
    int tail; // индекс последнего занятого элемента
    int count;// количество элементов в очереди
public:
    ArrayQueue(int _size = 16)
    {
        size = _size;
        count = 0;
        p = new int[size];
        head = -1;
        tail = 0;
    }
    ArrayQueue(const ArrayQueue& q)
    {
        size = q.size;
        p = new int[size];
        count = q.count;
        head = q.head;
        tail = q.tail;
        for (int i = 0; i < size; ++i)
        {
            p[i] = q.p[i];
        }
    }

    ~ArrayQueue()
    {
        delete[] p;
    }
    void push(const int &n)
    {
        if (IsFull())
        {
            throw "queue is full";
        }
        p[tail] = n;
        tail = (tail + 1) % size;
        if (head == -1)
        {
            head = 0;
        }
        count++;
    }
    void pop()
    {
        if (IsEmpty())
        {
            throw "queue is empty";
        }
        head = (head + 1) % size;
        count--;
    }
    bool IsEmpty() const
    {
        return count == 0;
    }
    bool IsFull() const
    {
        return count == size;
    }
    int Size() const
    {
        return count;
    }
    int Front() const
    {
        if (IsEmpty())
        {
            throw "queue is empty";
        }
        return p[head];
    }
    int Back() const
    {
        if (IsEmpty())
        {
            throw "queue is empty";
        }
        return p[(tail - 1 + size) % size];
    }
    void Show() const
    {
        if (IsEmpty())
        {
            cout << "Queue is empty" << endl;
            return;
        }

        int current = head;
        for (int i = 0; i < count; ++i)
        {
            cout << p[current] << " ";
            current = (current + 1) % size;
        }
        cout << endl;
    }
    friend class ArrayQueueIterator;
};
