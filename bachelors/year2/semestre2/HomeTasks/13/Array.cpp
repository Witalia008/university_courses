#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <iterator>

using namespace std;

class Array {
public:
    Array(){}
    Array(initializer_list<double> il) : elems(il) {}
    Array(int sz, double val) : elems(sz, val) {}
    Array(vector<double> _new) : elems(_new) {}

    virtual double getElem(int) = 0;
    virtual int size() = 0;
    virtual Array* add(Array*) = 0;
    virtual void foreach() = 0;
public:
    vector<double> elems;
};

class AndArray : Array {
public:
    AndArray() : Array() {}
    AndArray(initializer_list<double> il) : Array(il) {}
    AndArray(int sz, double val) : Array(sz, val) {}
    AndArray(vector<double> _new) : Array(_new) {}

    double getElem(int pos) {
        if (pos >= 0 && pos < size())
            return elems[pos];
        return numeric_limits<double>::quiet_NaN();
    }
    int size() {
        return elems.size();
    }
    Array* add(Array* other) {
        vector<double> res;
        for (int i = 0; i < size(); ++i) {
            bool found = false;
            double cur = getElem(i);
            for (int j = 0; !found && j < other->size(); ++j)
                found |= other->getElem(j) == cur;
            if (found)
                res.push_back(cur);
        }
        return (Array*)(new AndArray(res));
    }
    void foreach() {
        for (int i = 0; i < size(); ++i)
            if (elems[i] >= 0)
                elems[i] = pow(getElem(i), .5);
            else
                elems[i] = numeric_limits<double>::quiet_NaN();
    }
};

class OrArray : Array {
public:
    OrArray() : Array() {}
    OrArray(initializer_list<double> il) : Array(il) {}
    OrArray(int sz, double val) : Array(sz, val) {}
    OrArray(vector<double> _new) : Array(_new) {}

    double getElem(int pos) {
        if (pos >= 0 && pos < size())
            return elems[pos];
        return numeric_limits<double>::quiet_NaN();
    }
    int size() {
        return elems.size();
    }
    Array* add(Array* other) {
        vector<double> res = elems;
        for (int i = 0; i < other->size(); ++i)
            res.push_back(other->getElem(i));
        sort(res.begin(), res.end());
        vector<double>::iterator it = unique(res.begin(), res.end());
        res.resize(distance(res.begin(), it));
        return (Array*)(new OrArray(res));
    }
    void foreach() {
        for (int i = 0; i < size(); ++i)
            if (elems[i] >= 0)
                elems[i] = log(getElem(i));
            else
                elems[i] = numeric_limits<double>::quiet_NaN();
    }
};

void output(Array *arr) {
    for (int i = 0; i < arr->size(); ++i)
        cout << arr->getElem(i) << " ";
    cout << endl;
}

int main()
{
    Array* a = (Array*)(new AndArray({1., 2., 3., 4., 5.}));
    Array* b = (Array*)(new OrArray({3., 4., 5., 6., 7.}));
    Array* c = a->add(b);
    Array* d = b->add(a);
    a->foreach();
    b->foreach();
    output(a);
    output(b);
    output(c);
    output(d);
    return 0;
}
