#pragma once
#include "ProtectedArray.h"
#include "Stack.h"

template <class Elem>
class BoundedStackDerivedFromArray : protected ProtectedArray<Elem>, public Stack<Elem>
{
private:
    static const int bos; //bottom of stack
protected:
    int _top;

public:
    class BadStack{};
    explicit BoundedStackDerivedFromArray(int size) :
        ProtectedArray(size), _top(bos){};
    bool empty() const
    {
        return _top == bos;
    }
    bool full() const
    {
        return _top == size() - 1;
    }
    const Elem& top() const
    {
        return ia[_top];
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
        ia[++_top] = value;
    }
};
