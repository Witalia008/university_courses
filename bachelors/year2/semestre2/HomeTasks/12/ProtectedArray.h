#pragma once
#include <memory.h>

template <class Elem>
class ProtectedArray
{
public:
    ProtectedArray(int sz = defaultProtectedArraySize) {
        _size = sz;
        ia = new Elem[sz];
    }
    ProtectedArray(const ProtectedArray& other) {
        init(other._size, other.ia);
    }
    ~ProtectedArray() { delete[]ia; }

    bool operator== (const ProtectedArray& other) const {
        if (_size != other._size)
            return false;
        for (int i = 0; i < _size; ++i) {
            if (ia[i] != other.ia[i])
                return false;
        }
        return true;
    }
    bool operator!= (const ProtectedArray& other) const {
        return !(*this == other);
    }

    ProtectedArray& operator= (const ProtectedArray& other) {
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

    int size() const { return _size; }
protected:
    Elem *ia;
private:
    int _size;
    static const int defaultProtectedArraySize;
    void init(int sz, Elem* arr) {
        _size = sz;
        memcpy(ia, arr, sizeof(arr));
    }
};

template<class Elem>
const int ProtectedArray<Elem>::defaultProtectedArraySize = 256;
