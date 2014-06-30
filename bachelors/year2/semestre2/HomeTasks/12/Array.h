#pragma once
#include <memory.h>

template <class Elem>
class Array
{
public:
    Array(int sz = defaultArraySize) {
        _size = sz;
        ia = new Elem[sz];
    }
    Array(const Array& other) {
        init(other._size, other.ia);
    }
    ~Array() { delete[]ia; }

    bool operator== (const Array& other) const {
        if (_size != other._size)
            return false;
        for (int i = 0; i < _size; ++i) {
            if (ia[i] != other.ia[i])
                return false;
        }
        return true;
    }
    bool operator!= (const Array& other) const {
        return !(*this == other);
    }

    Array& operator= (const Array& other) {
        init(other._size, other.ia);
        return *this;
    }
    Elem& operator[] (int index) {
        return ia[index];
    }
    //    ���������� ������������ �������� ������
    //    ��� ��������� �������
    //    Elem BoundedStack::top() const
    Elem& operator[] (int index) const {
        return ia[index];
    }

    int size() const {
        return _size;
    }

private:
    int _size;
    Elem *ia;
    static const int defaultArraySize;
    void init(int sz, Elem* arr) {
        _size = sz;
        memcpy(ia, arr, sizeof(arr));
    }
};

template<class Elem>
const int Array<Elem>::defaultArraySize = 256;
