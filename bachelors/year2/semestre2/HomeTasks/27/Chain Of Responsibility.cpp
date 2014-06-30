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

class ATM {
protected:
    ATM* next;
public:
    ATM() {
        next = nullptr;
    }
    void setNext(ATM* _next) {
        next = _next;
    }
    void add(ATM* _next) {
        if (next == nullptr)
            next = _next;
        else
            next->add(_next);
    }
    virtual void withdraw(int amount) {
        if (!amount) return;
        if (next != nullptr)
            next->withdraw(amount);
    }
};

class Currency : public ATM {
    int val;
public:
    Currency(int _st) : ATM(), val(_st) {}
    void withdraw(int amount) override {
        if (amount / val)
            cout << amount / val << "x" << val << "$" << endl;
        ATM::withdraw(amount % val);
    }
};

#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ATM atm;
    int x[9] = { 500, 200, 100, 50, 20, 10, 5, 2, 1 };
    Currency* a[9];
    for (int i = 0; i < 9; ++i) {
        a[i] = new Currency(x[i]);
        atm.add(a[i]);
    }
    atm.withdraw(798);
    system("pause");
    return 0;
}