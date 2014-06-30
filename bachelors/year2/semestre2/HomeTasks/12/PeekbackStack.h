#pragma once
#include "BoundedStackDerivedFromArray.h"

template <class Elem>
class PeekbackStack : public BoundedStackDerivedFromArray<Elem>
{
public:
    PeekbackStack(int size) :BoundedStackDerivedArray(size){};
    bool peekback(int x, Elem& res) const {
        if (BoundedStackDerivedFromArray::empty())
            return false;
        res = BoundedStackDerivedFromArray::top();
        BoundedStackDerivedFromArray::pop();
        return true;
    }
};
