#pragma once
#include "CyclicArray.h"

template<class Elem>
class Queue : public CyclicArray<Elem> {
public:
    Queue(int sz) : CyclicArray(sz) {
        last = 0;
        rsize = 0;
    }
    void push(const Elem& el) {
        ia[last] = el;
        last = (last + 1) % _size;
        rsize = min(rsize + 1, _size);
    }
    void pop() {
        if (!rsize)
            return;
        first = (first + 1) % _size;
        --rsize;
    }
    Elem front() {
        return ia[first];
    }
    int size() {
        return rsize;
    }
protected:
    int last;
    int rsize;
};