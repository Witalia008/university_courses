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
    class iterator {
    protected:
        iterator() {}
    public:
        virtual void begin(const Container<T>*) = 0;
        virtual void next() = 0;
        virtual void start() = 0;
        virtual T get() const = 0;
        virtual bool end() const = 0;
    };
    virtual void insert(const T&) = 0;
    virtual void insert(T&&) = 0;
    virtual void erase(const T&) throw(OutOfBoundsException) = 0;
    virtual void erase(T&&) throw(OutOfBoundsException) = 0;
    virtual bool find(const T&) const = 0;
    virtual bool find(T&&) const = 0;
    virtual int size() const = 0;
    virtual bool empty() const = 0;
    virtual T& get(int) const throw(OutOfBoundsException) = 0;
    virtual iterator&& begin() const = 0;
    virtual iterator&& end() const = 0;
    virtual ~Container() {}
};

template<class T>
class ConcreteContainer : public Container<T> {
protected:
    Container<T> *_data;
public:
    class concrete_iterator : virtual public iterator {
        Container<T>::iterator *item, *_start;
    public:
        concrete_iterator() { item = _start = nullptr; }
        virtual void begin(const Container<T> *ct) override {
            _start = item = &ct->begin();
        }
        virtual void next() override {
            item->next();
        }
        virtual void start() override {
            item = _start;
        }
        virtual T get() const override {
            return item->get();
        }
        bool end() const override {
            return item->end();
        }
    };
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
    virtual T& get(int idx) const throw(OutOfBoundsException) {
        return _data->get(idx);
    }
    virtual concrete_iterator&& begin() const {
        concrete_iterator res;
        res.begin(this);
        return move(res);
    }
    virtual concrete_iterator&& end() const {
        concrete_iterator res;
        return move(res);
    }
    virtual ~ConcreteContainer() {
        _data->~Container();
        delete _data;
    }
};

template<class T>
class Vector : public Container<T>, public vector<T> {
public:
    class vect_iterator : virtual public Container<T>::iterator {
        const Container<T> *targ;
        int *item, *_start;
    public:
        vect_iterator() { item = _start = nullptr; }
        virtual void begin(const Container<T> *ct) override {
            if (ct->size())
                item = _start = &ct->get(0);
            targ = ct;
        }
        virtual void next() override {
            item++;
        }
        virtual void start() override {
            item = _start;
        }
        virtual T get() const override {
            return *item;
        }
        bool end() const override {
            return (item - _start) >= targ->size();
        }
    };
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
    virtual T& get(int idx) const throw(OutOfBoundsException) {
        if (idx < 0 | idx >= size())
            throw OutOfBoundsException();
        vector<T>::iterator it;
        advance(it, idx);
        return *it;
    }
    virtual vect_iterator&& begin() const {
        vect_iterator res;
        res.begin(this);
        return move(res);
    }
    virtual vect_iterator&& end() const {
        vect_iterator res;
        return move(res);
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
    for (ConcreteContainer<int>::concrete_iterator it = st.begin(); !it.end(); it.next())
        cout << it.get() << " ";
    cout << endl;
    system("pause");
    return 0;
}