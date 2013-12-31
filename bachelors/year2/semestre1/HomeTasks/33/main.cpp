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

using carr = valarray<int>;

struct Diofant {
    int n;
    carr a, x;
    int gcd, c;
};

void read(Diofant &a) {
    cin >> a.n;
    a.a.resize(a.n);
    for (int & i : a.a)
        cin >> i;
    cin >> a.c;
}

void set_one(carr &x, int pos) {
    for (int & i : x)
        i = 0;
    x[pos] = 1;
}

void swap_coefs(carr &a, carr &b, int q) {
    a -= b * q;
    swap(a, b);
}

void solve(Diofant &eq) {
    eq.x.resize(eq.n);
    set_one(eq.x, 0);
    eq.gcd = eq.a[0];
    for (int i = 1; i < eq.n; ++i) {
        valarray<int> xx(eq.n);
        set_one(xx, i);
        int ax = eq.a[i];
        while (ax) {
            swap_coefs(eq.x, xx, eq.gcd / ax);
            eq.gcd %= ax;
            swap(eq.gcd, ax);
        }
    }
}

void write(Diofant &eq) {
    cout << "GCD = " << eq.gcd << endl;
    for (int i = 0; i < eq.n; ++i) {
        cout << eq.a[i] << "*" << eq.x[i] * (eq.c / eq.gcd) << (i == eq.n - 1 ? " = " : " + ");
    }
    cout << eq.c << endl;
}

//#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    Diofant equation;
    read(equation);
    solve(equation);
    write(equation);
    return 0;
}