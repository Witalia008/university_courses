#include "SortPack.h"

bool IntToSort::operator<(const SortedItems& other) const {
    return this->value < dynamic_cast<const IntToSort&>(other).value;
}

void IntToSort::showItem() {
    cout << value;
}

void IntToSort::swap(SortedItems* other) {
    IntToSort * sp = (IntToSort*)other;
    std::swap(value, sp->value);
}

ArrayOfInt::ArrayOfInt(int len) {
    length = len;
    arrayToSort = new IntToSort[len];
}

ArrayOfInt::~ArrayOfInt() {
    delete[] arrayToSort;
}

SortedItems& ArrayOfInt::operator[](int idx) {
    return arrayToSort[idx];
}

void ArrayOfInt::fill() {
    for (int i = 0; i < length; ++i)
        arrayToSort[i] = rand();
}

void ArrayOfInt::show() {
    for (int i = 0; i < length; ++i) {
        arrayToSort[i].showItem();
        cout << " ";
    }
    cout << endl;
}

void SortPack::attach(ArrayOfItems& arr, int len) {
    items = &arr;
    quantity = len;
}

void SortPack::discardCounter() {
    counter = 0;
}

void SortPack::increaseConter() {
    ++counter;
}

void SortPack::show() {
    cout << counter << endl;
    cout << quantity << endl;
    items->show();
}

void SortPack::bubble() {
    discardCounter();
    for (int j = quantity - 1; j > 0; --j) {
        for (int i = 0; i < j; ++i) {
            if ((*items)[i + 1] < (*items)[i])
                (*items)[i].swap(&(*items)[i + 1]);
            increaseConter();
        }
    }
}

void SortPack::select() {
    discardCounter();
    for (int i = 0; i + 1 < quantity; ++i) {
        int targ = i;
        for (int j = i + 1; j < quantity; ++j) {
            if ((*items)[j] < (*items)[targ])
                targ = j;
            increaseConter();
        }
        if (i != targ)
            (*items)[targ].swap(&(*items)[i]);
    }
}

void SortPack::insert() {
    discardCounter();
    for (int i = 1; i < quantity; ++i) {
        for (int j = i; j > 0 && (increaseConter(), (*items)[j] < (*items)[j - 1]); --j)
            (*items)[j].swap(&(*items)[j - 1]);
    }
}

void SortPack::shell() {
    discardCounter();
    
    int max_bit = 1;
    while ((max_bit << 1) <= quantity) max_bit <<= 1;

    for (int d = max_bit - 1; d > 0; d = ((d + 1) >> 1) - 1) {
        for (int i = d; i < quantity; ++i) {
            for (int j = i; j >= d && (increaseConter(), (*items)[j] < (*items)[j - d]); j -= d) {
                (*items)[j].swap(&(*items)[j - d]);
            }
        }
    }
}

void SortPack::quick() {
    discardCounter();
    quickSort(0, quantity - 1);
}

void SortPack::quickSort(int l, int r) {
    if (r - l < 2) {
        if (r > l && (increaseConter(), (*items)[r] < (*items)[l]))
            (*items)[l].swap(&(*items)[r]);
        return;
    }
    int i = l, j = r, et = (l + r) / 2;
    while (i < j) {
        while (increaseConter(), (*items)[i] < (*items)[et])
            ++i;
        while (increaseConter(), (*items)[et] < (*items)[j])
            --j;
        if (i < j) {
            (*items)[i].swap(&(*items)[j]);
            if (i == et || j == et)
                et ^= i ^ j;
            ++i; --j;
        }
    }
    if (j > l) quickSort(l, j);
    if (i < r) quickSort(i, r);
}