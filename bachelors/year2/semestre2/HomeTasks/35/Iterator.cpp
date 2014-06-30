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
#include <initializer_list>


using namespace std;
using namespace std::chrono;

typedef long long ll;

const int N = 100005;
const int K = 505;
const ll InfL = 1000000000000000000LL;
const int MOD = 1000000007;

class Stack {
    vector<int> st;
    friend class StackIterator;
public:
    void push(int in) {
        st.push_back(in);
    }
    void pop() {
        if (!empty())
            st.pop_back();
    }
    bool empty() {
        st.empty();
    }
    int top() {
        return st.back();
    }
    StackIterator* createIter() const;
};

class StackIterator {
    const Stack *st;
    int index;
public:
    StackIterator(const Stack *it) {
        st = it;
        index = 0;
    }
    void first() {
        index = 0;
    }
    void next() {
        index++;
    }
    bool isEnd() {
        return index == st->st.size();
    }
    int currentElement() {
        return st->st[index];
    }
};

StackIterator* Stack::createIter() const {
    return new StackIterator(this);
}

void output(Stack &st) {
    StackIterator *it = st.createIter();
    for (; !it->isEnd(); it->next())
        cout << it->currentElement() << " ";
    cout << endl;
}

#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    Stack st;
    for (int i = 0; i < 20; ++i)
        st.push(rand() % 40);
    output(st);
    system("pause");
    return 0;
}