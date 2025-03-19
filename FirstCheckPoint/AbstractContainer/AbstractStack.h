#pragma once
#include "AbstractContainer.h"
class AbstractStack : public AbstractContainer
{
public:
    virtual ~AbstractStack() {};
    virtual int Top() const = 0;	//верхний элемент стека
};