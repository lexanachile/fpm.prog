#pragma once
#include "AbstractQueue.h"

struct node
{
    int info;
    node* next;
};

class ListQueue : public AbstractQueue
{
protected:
    node* head;
    node* tail;
public:
    ListQueue() : head(nullptr), tail(nullptr)
    {
    }

    ListQueue(const ListQueue& el)
    {
        head = nullptr;
        tail = nullptr;
        for (auto i = el.head; i != nullptr; i = i->next)
        {
            push(i->info);
        }
    }

    void push(const int &info)
    {
        node* temp = new node;
        temp->info = info;
        temp->next = nullptr;
        if (tail == nullptr)
            head = temp;
        else
            tail->next = temp;
        tail = temp;
    }

    void pop()
    {
        if (head == nullptr)
        {
            throw "Queue is empty";
        }
        node* temp = head;
        head = head->next;
        delete temp;

        if (head == nullptr)
            tail = nullptr;
    }

    int Size() const
    {
        node* temp = head;
        int i = 0;
        while (temp != nullptr)
        {
            i++;
            temp = temp->next;
        }
        return i;
    }

    int Front() const
    {
        if (head == nullptr)
        {
            throw "Queue is empty";
        }
        return head->info;
    }

    int Back() const
    {
        if (tail == nullptr)
        {
            throw "Queue is empty";
        }
        return tail->info;
    }

    void Show() const
    {
        if (head == nullptr)
        {
            throw "Queue is empty";
        }

        node* current = head;
        while (current != nullptr)
        {
            cout << current->info << " ";
            current = current->next;
        }
        cout << endl;
    }

    bool IsEmpty() const
    {
        return head == nullptr;
    }

    ~ListQueue()
    {
        while (head != nullptr)
        {
            node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }
    friend class ListQueueIterator;
};