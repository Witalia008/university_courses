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

const int N = 100005;
const int K = 505;
const ll InfL = 1000000000000000000LL;
const int MOD = 1000000007;

class StackImpl
{
public:
    virtual void push(int) = 0;
    virtual void pop() = 0;
    virtual bool empty() = 0;
    virtual int top() = 0;
};

class StackStand : public StackImpl, public stack<int> { 
    void push(int in) override {
        stack<int>::push(in);
    }
    void pop() override {
        stack<int>::pop();
    }
    bool empty() override {
        return stack<int>::empty();
    }
    int top() override {
        return stack<int>::top();
    }
};

class StackMine : public StackImpl {
    int total;
    int capacity;
    int *arr;
    void clear(int *fr, int *to) {
        for (int* i = fr; i != to; ++i)
            *i = 0;
    }
    void resize(int new_cap) {
        int *b = new int[new_cap];
        clear(b, b + new_cap);
        copy(arr, arr + min(capacity, new_cap), b);
        swap(arr, b);
        capacity = new_cap;
        delete[] b;
    }
    void check() {
        if (total == capacity)
            resize(capacity * 2);
        else if (total < capacity / 2 && capacity > 2)
            resize(capacity / 2);
    }
public:
    StackMine() {
        capacity = 2;
        arr = new int[capacity];
        clear(arr, arr + capacity);
        total = 0;
    }
    void push(int in) override {
        check();
        arr[total++] = in;
    }
    void pop() override {
        if (!empty()) {
            --total;
            check();
        }
    }
    int top() override {
        return arr[total - 1];
    }
    bool empty() override {
        return total == 0;
    }
};

class Stack
{
public:
    enum StackType {Standard, Custom};
    Stack(StackType type) {
        if (type == StackType::Standard)
            st = new StackStand();
        else
            st = new StackMine();
    }
    Stack() : Stack(StackType::Standard) {}
    ~Stack() {
        delete st;
    }
    virtual void push(int in) {
        st->push(in);
    }
    virtual void pop() {
        st->pop();
    }
    virtual bool empty() {
        return st->empty();
    }
    virtual int top() {
        return st->top();
    }
protected:
    StackImpl *st;
};

class StackHanoi : public Stack
{
public:
    StackHanoi(StackType type) : Stack(type), totalRejected(0) {}
    StackHanoi() : StackHanoi(StackType::Standard) {}
    ~StackHanoi() {}
    int reportRejected() { return totalRejected; }
    void push(int in) override {
        if (!empty() && top() > in)
            ++totalRejected;
        else
            Stack::push(in);
    }
private:
    int totalRejected;
};

#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    Stack* stacks[4] = { new Stack(), new Stack(Stack::StackType::Custom),
        new StackHanoi(), new StackHanoi(Stack::StackType::Custom) };
    for (int i = 0; i < 20; ++i) {
        int num = rand() % 40;
        for (int j = 0; j < 4; ++j)
            stacks[j]->push(num);
    }
    for (int i = 0; i < 4; ++i) {
        while (!stacks[i]->empty()) {
            cout << stacks[i]->top() << " ";
            stacks[i]->pop();
        }
        cout << endl;
    }
    cout << "Total rejected: " << ((StackHanoi*)stacks[3])->reportRejected() << endl;
    system("pause");
    return 0;
}