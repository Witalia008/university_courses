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

#define Cpp11
#ifdef Cpp11
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
using namespace std::chrono;
#endif
using namespace std;

typedef double ld;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;

//const int mx[4] = { 1, 0, -1, 0 };
//const int my[4] = { 0, 1, 0, -1 };

const int Inf = 1000000000;
const int Mi = 1000003;
const int N = 300005;
const int M = 100005;
//const int K = 20;
const ld eps = 10e-8;
const ld PI = 2 * acos(0.0);
const ll InfLL = ll(Inf) * ll(Inf);

unsigned rand16() { return rand() % (1 << 16); }
unsigned rand32() { return (rand16() << 16) + rand16(); }
ull rand64() { return (((ull)rand32()) << 32) + rand32(); }
int rand(int L, int R)
{
    if (L > R)
        return R;
    return rand32() % (R - L + 1) + L;
}
ld random(ld L, ld R) { return rand(ceil((L - eps) * 100), floor((R + eps) * 100)) / 100.0; }

ll Abs(ll a) { return a < 0 ? -a : a; }
ll sqr(ll a) { return a * a; }
ll gcd(ll a, ll b) { return !b ? a : gcd(b, a % b); }

string toStr(int n)
{
    char s[100];
    sprintf(s, "%d", n);
    return string(s);
}

const string alph = "0123456789ABCDEFGHIJKLMNOPQRSTUWVXYZ";

struct Num
{
    int base;
    vector<int> n;

    Num() {}

    Num(ll n, int b)
    {
        while (n)
        {
            this->n.push_back(n % b);
            n /= b;
        }
        this->base = b;
    }

    ll to10()
    {
        ll res = 0;
        for (int i = this->n.size() - 1; i >= 0; --i)
        {
            res = res * this->base + this->n[i];
        }
        return res;
    }

    void shift(int k)
    {
        int m = this->n.size();
        this->n.resize(m + k);
        for (int i = m - 1; i >= 0; --i)
        {
            this->n[i + k] = this->n[i];
            this->n[i] = 0;
        }
    }

    bool bigger(Num b)
    {
        if (this->n.size() != b.n.size())
        {
            return this->n.size() > b.n.size();
        }
        for (int i = this->n.size() - 1; i >= 0; --i)
        {
            if (this->n[i] != b.n[i])
            {
                return this->n[i] > b.n[i];
            }
        }
        return false;
    }

    void output()
    {
        for (int i = this->n.size() - 1; i >= 0; --i)
        {
            cout << alph[this->n[i]];
        }
        cout << "(" << this->base << ")" << endl;
    }
};

Num add(Num a, Num b)
{
    if (a.base != b.base)
        return Num{};
    Num res;
    res.base = a.base;

    for (int i = 0, p = 0; i < a.n.size() || i < a.n.size() || p; ++i)
    {
        int cur = (i < a.n.size() ? a.n[i] : 0) +
                  (i < b.n.size() ? b.n[i] : 0) + p;
        res.n.push_back(cur % res.base);
        p = cur / res.base;
    }
    return res;
}

Num mult(Num a, Num b)
{
    if (a.base != b.base)
        return Num{};
    Num res;
    res.base = a.base;

    for (int i = 0; i < a.n.size(); ++i)
    {
        for (int j = 0, p = 0; j < b.n.size() || p; ++j)
        {
            if (i + j == res.n.size())
                res.n.push_back(0);
            int cur = a.n[i] * (j < b.n.size() ? b.n[j] : 0) + p + res.n[i + j];
            res.n[i + j] = cur % res.base;
            p = cur / res.base;
        }
    }
    return res;
}

Num sub(Num a, Num b)
{
    if (a.base != b.base)
        return Num{};
    Num res;
    res.base = a.base;

    for (int i = 0, p = 0; i < a.n.size() || i < b.n.size() || p; ++i)
    {
        int cur = (i < a.n.size() ? a.n[i] : 0) - (i < b.n.size() ? b.n[i] : 0) - p;
        p = cur < 0;
        res.n.push_back(cur + p * res.base);
    }
    while (res.n.size() > 1 && res.n.back() == 0)
        res.n.pop_back();

    return res;
}

pair<Num, Num> div(Num a, Num b)
{
    if (a.base != b.base)
        return make_pair(Num{}, Num{});
    Num q, r;
    r.base = q.base = a.base;

    q.n.resize(a.n.size());
    for (int i = a.n.size() - 1; i >= 0; --i)
    {
        r.shift(1);
        r.n[0] = a.n[i];
        while (r.bigger(b))
        {
            r = sub(r, b);
            ++q.n[i];
        }
    }
    while (q.n.size() > 1 && q.n.back() == 0)
        q.n.pop_back();
    return make_pair(q, r);
}

Num translate(Num a, int b)
{
    return Num(a.to10(), b);
}

//#define ONLINE_JUDGE
int main()
{
    std::ios_base::sync_with_stdio(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    Num(12391723, 16).output();
    add(Num(27, 8), Num(10, 8)).output();
    mult(Num(27, 8), Num(10, 8)).output();
    sub(Num(27, 8), Num(10, 8)).output();
    auto t = div(Num(27, 8), Num(10, 8));
    t.first.output();
    t.second.output();
    translate(Num(12391723, 8), 16).output();

    auto start = clock();
    for (int i = 0; i < 1000000; ++i)
    {
        Num(rand() % Inf, rand() % 30 + 2);
    }
    cout << clock() - start << endl;
    return 0;
}