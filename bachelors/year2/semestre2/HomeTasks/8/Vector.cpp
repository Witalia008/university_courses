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

class OutOfBoundsException : public exception {
public:
    virtual const char * what() const override {
        return "Index out of bounds";
    }
};

template<class T>
class Container {
public:
    virtual void insert(const T&) = 0;
    virtual void insert(T&&) = 0;
    virtual void erase(const T&) throw(OutOfBoundsException) = 0;
    virtual void erase(T&&) throw(OutOfBoundsException) = 0;
    virtual bool find(const T&) const = 0;
    virtual bool find(T&&) const = 0;
    virtual int size() const = 0;
    virtual bool empty() const = 0;
    virtual T get(int) const throw(OutOfBoundsException) = 0;
    virtual ~Container() {}
};

template<class T>
class ConcreteContainer : public Container<T> {
protected:
    Container<T> *_data;
public:
    ConcreteContainer(Container<T> *data) : _data(data) {}
    virtual void insert(const T& val) override {
        _data->insert(val);
    }
    virtual void insert(T&& val) override {
        _data->insert(val);
    }
    virtual void erase(const T& val) throw(OutOfBoundsException) override {
        _data->erase(val);
    }
    virtual void erase(T&& val) throw(OutOfBoundsException) override {
        _data->erase(val);
    }
    virtual bool find(const T& val) const override {
        return _data->find(val);
    }
    virtual bool find(T&& val) const override{
        return _data->find(val);
    }
    virtual int size() const {
        return _data->size();
    }
    virtual bool empty() const {
        return _data->empty();
    }
    virtual T get(int idx) const throw(OutOfBoundsException) {
        return _data->get(idx);
    }
    virtual ~ConcreteContainer() {
        _data->~Container();
        delete _data;
    }
};

template<class T>
class Set : public Container<T>, public set<T> {
public:
    Set() {}
    virtual void insert(const T& val) override {
        set<T>::insert(val);
    }
    virtual void insert(T&& val) override {
        set<T>::insert(val);
    }
    virtual void erase(const T& val) throw(OutOfBoundsException) override {
        if (!find(val))
            throw OutOfBoundsException();
        set<T>::erase(val);
    }
    virtual void erase(T&& val) throw(OutOfBoundsException) override {
        if (!find(val))
            throw OutOfBoundsException();
        set<T>::erase(val);
    }
    virtual bool find(const T& val) const override {
        return set<T>::find(val) != set<T>::end();
    }
    virtual bool find(T&& val) const override{
        return set<T>::find(val) != set<T>::end();
    }
    virtual int size() const {
        return set<T>::size();
    }
    virtual bool empty() const {
        return set<T>::empty();
    }
    virtual T get(int idx) const throw(OutOfBoundsException) {
        if (idx < 0 | idx >= size())
            throw OutOfBoundsException();
        set<T>::iterator it;
        advance(it, idx);
        return *it;
    }
    virtual ~Set() {
        
    }
};

template<class T>
class Vector : public Container<T>, public vector<T> {
public:
    Vector() {}
    virtual void insert(const T& val) override {
        vector<T>::push_back(val);
    }
    virtual void insert(T&& val) override {
        vector<T>::emplace_back(val);
    }
    virtual void erase(const T& val) throw(OutOfBoundsException) override {
        if (!find(val))
            throw OutOfBoundsException();
        vector<T>::erase(std::find(vector<T>::begin(), vector<T>::end(), val));
    }
    virtual void erase(T&& val) throw(OutOfBoundsException) override {
        if (!find(val))
            throw OutOfBoundsException();
        vector<T>::erase(std::find(vector<T>::begin(), vector<T>::end(), val));
    }
    virtual bool find(const T& val) const override {
        return std::find(vector<T>::begin(), vector<T>::end(), val) != vector<T>::end();
    }
    virtual bool find(T&& val) const override{
        return std::find(vector<T>::begin(), vector<T>::end(), val) != vector<T>::end();
    }
    virtual int size() const {
        return vector<T>::size();
    }
    virtual bool empty() const {
        return vector<T>::empty();
    }
    virtual T get(int idx) const throw(OutOfBoundsException) {
        if (idx < 0 | idx >= size())
            throw OutOfBoundsException();
        vector<T>::iterator it;
        advance(it, idx);
        return *it;
    }
    virtual ~Vector() {

    }
};

#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ConcreteContainer<int> st((Container<int>*)(new Vector<int>()));
    for (int i = 0; i < 20; ++i)
        st.insert(rand() % 20);
    for (int i = 0; i < 20; ++i)
        cout << st.find(i) << " ";
    cout << endl;
    system("pause");
    return 0;
}