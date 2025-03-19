#pragma once
#include "AbstractStack.h"

struct node
{
    int info;
    node* next;
};

class ListStack : public AbstractStack
{
protected:
    node* head;
public:
    ListStack() : head(nullptr) {}

    ~ListStack()
    {
        node* temp;
        while (head != nullptr)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    ListStack(const ListStack& x)
    {
        head = nullptr;
        node* temp;
        ListStack y;
        temp = x.head;
        while (temp != nullptr)
        {
            y.push(temp->info);
            temp = temp->next;
        }
        temp = y.head;
        while (temp != nullptr)
        {
            push(temp->info);
            temp = temp->next;
        }
    }

    void push(const int &x)
    {
        node* temp = new node;
        temp->info = x;
        temp->next = head;
        head = temp;
    }

    void pop()
    {
        if (head == nullptr)
        {
            throw "Stack is empty";
        }
        node* temp = head;
        head = head->next;
        delete temp;
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

    int Top() const
    {
        if (head == nullptr)
        {
            throw "Stack is empty";
        }
        return head->info;
    }

    bool IsEmpty() const
    {
        return head == nullptr;
    }

    void Show() const
    {
        if (head == nullptr)
        {
            throw "Stack is empty";
        }
        node* temp = head;
        while (temp != nullptr)
        {
            cout << temp->info << endl;
            temp = temp->next;
        }
    }

    friend class ListStackIterator;
};