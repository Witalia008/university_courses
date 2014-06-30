#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <string>
#include <memory.h>
#include <map>
#define _USE_MATH_DEFINES
#include <math.h>
#include <list>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <queue>
#include <stack>
#include <complex>
#include <limits.h>
#include <cassert>
#include <chrono>
#include <regex>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <valarray>

using namespace std;
using namespace std::chrono;

typedef long long ll;

const int N = 16005;
const int K = 605;
const ll InfL = 1000000000000000000LL;
const int MOD = 1000000007;

class StackNoDataException : public exception {
public:
    const char *what() const override {
        return "StackIsEmpty";
    }
};


template <class T>
class Stack {
protected:
    vector<T> _data;
public:
    Stack() {}
    Stack(initializer_list<T> lst) : _data(lst) {}
    virtual T& top() throw(StackNoDataException) {
        if (_data.size() == 0) {
            throw StackNoDataException();
        }
        return _data[_data.size() - 1];
    }
    virtual void pop() throw (StackNoDataException) {
        if (_data.size() == 0) {
            throw StackNoDataException();
        }
        _data.pop_back();
    }
    virtual void push(const T& nData) {
        _data.push_back(nData);
    }
    virtual void push(T && data) {
        _data.emplace_back(data);
    }
    virtual int size() const {
        return _data.size();
    }
    virtual bool empty() {
        return size() == 0;
    }
    virtual void swap(Stack<T> other) {
        other._data.swap(_data);
    }
    virtual Stack<T>& operator= (const Stack<T>& other) {
        _data = other._data;
        return *this;
    }
    virtual ~Stack() {
        _data.clear();
    }
};

#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    Stack<int> c;
    c.push(1);
    cout << c.top() << endl;
    c.top() = 2;
    cout << c.top() << endl;
    system("pause");
    return 0;
}