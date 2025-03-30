#pragma once
#include "AbstractContainer.h"
class AbstractQueue : public AbstractContainer
{
public:
    virtual ~AbstractQueue() {};
    virtual int Front() const = 0;	//первый элемент очереди
    virtual int Back() const = 0;	//последний элемент очереди
};