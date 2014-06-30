#pragma once
#include "Stack.h"
#include "Array.h"

template <class Elem>
class BoundedStackAgregatingArray : public Stack<Elem>
{
private:
    static const int bos; //bottom of stack
    int _top;
    Array<Elem> stackArray;

public:
    class BadStack{};
    explicit BoundedStackAgregatingArray(int size) :
        stackArray(size), _top(bos){};
    bool empty() const
    {
        return _top == bos;
    }
    bool full() const
    {
        return _top == stackArray.size() - 1;
    }
    const Elem& top() const
    {
        return stackArray[_top];
    }
    void pop()
    {
        if (empty())
            throw BadStack();
        _top--;
    }
    void push(const Elem& value)
    {
        if (full())
            throw BadStack();
        stackArray[++_top] = value;
    }
    //delegating:
    int size() const
    {
        return stackArray.size();
    }
};

template<class Elem>
const int BoundedStackAgregatingArray<Elem>::bos = -1;

