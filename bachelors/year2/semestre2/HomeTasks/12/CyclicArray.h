#pragma once
#include <memory.h>

template <class Elem>
class CyclicArray
{
public:
    CyclicArray(int sz = defaultArraySize) {
        _size = sz;
        ia = new Elem[sz];
        first = 0;
    }
    CyclicArray(const CyclicArray& other) {
        first = other.first;
        init(other._size, other.ia);
    }
    ~CyclicArray() { delete[]ia; }

    bool operator== (const CyclicArray& other) const {
        if (_size != other._size)
            return false;
        for (int i = 0; i < _size; ++i) {
            if (ia[(i + first) % _size] != other.ia[(i + other.first) % other._size])
                return false;
        }
        return true;
    }
    bool operator!= (const CyclicArray& other) const {
        return !(*this == other);
    }

    CyclicArray& operator= (const CyclicArray& other) {
        init(other._size, other.ia);
        first = other.first;
        return *this;
    }
    Elem& operator[] (int index) {
        return ia[(index + first) % _size];
    }
    //    ���������� ������������ �������� ������
    //    ��� ��������� �������
    //    Elem BoundedStack::top() const
    Elem& operator[] (int index) const {
        return ia[(index + first) % _size];
    }

    int size() const {
        return _size;
    }

protected:
    int _size;
    int first;
    Elem *ia;
    static const int defaultArraySize;
    void init(int sz, Elem* arr) {
        _size = sz;
        memcpy(ia, arr, sizeof(arr));
    }
};

template<class Elem>
const int CyclicArray<Elem>::defaultArraySize = 256;
