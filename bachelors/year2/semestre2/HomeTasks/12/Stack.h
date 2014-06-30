#pragma once

template <class Elem>
class Stack
{
public:
    Stack(){}
    virtual bool empty() const=0;
    virtual const Elem& top() const=0;
    virtual void pop()=0;
    virtual void push(const Elem& value)=0;
};
