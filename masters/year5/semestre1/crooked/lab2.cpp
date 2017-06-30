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
const int Mi = 1000000009;
const int N = 10005;
const int M = 100005;
//const int K = 20;
const ld eps = 10e-7;
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

double evaluate(const vector<double> &a, double x)
{
    double res = a[0];
    double power = 1;
    for (int i = 1; i < a.size(); ++i)
    {
        power *= x;
        res += a[i] * power;
    }
    return res;
}

double Horner(const vector<double> &a, double x)
{
    double res = 0;
    for (int i = a.size() - 1; i >= 0; --i)
    {
        res = res * x + a[i];
    }
    return res;
}

struct Tree
{
    vector<double> *a;
    Tree *q, *r;
    double b;
    int j;

    Tree()
    {
        a = nullptr;
        q = r = nullptr;
    }
};

Tree *build(vector<double> a)
{
    Tree *res = new Tree();
    if (a.size() <= 2)
    {
        res->a = new vector<double>(a);
    }
    else
    {
        int n = a.size();
        res->j = n >> 1;
        res->b = a[res->j - 1] - 1;
        vector<double> q, r = a;
        for (int i = 0; i < res->j; ++i)
        {
            double cur = r.back();
            r.pop_back();
            r[res->j - i - 1] -= cur * res->b;
            q.push_back(cur);
        }
        reverse(q.begin(), q.end());
        res->q = build(q);
        res->r = build(r);
    }
    return res;
}

double evaluate(Tree *t, double x)
{
    if (t->a != nullptr)
    {
        return evaluate(*t->a, x);
    }
    double Q = evaluate(t->q, x);
    double R = evaluate(t->r, x);
    return (pow(x, t->j) + t->b) * Q + R;
}

double fourier(const vector<double> &a, double x)
{
    if (a.size() <= 1)
    {
        return a.size() ? a[0] : 0;
    }
    vector<double> a0, a1;
    for (int i = 0; i < a.size(); ++i)
    {
        (i % 2 ? a1 : a0).push_back(a[i]);
    }
    return fourier(a0, x * x) + x * fourier(a1, x * x);
}

//#define ONLINE_JUDGE
int main()
{
    std::ios_base::sync_with_stdio(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    vector<double> a;
    a = {-3, 2, 9, 6, -8, 0, 4, 1};
    a.resize(511);
    for (int i = 0; i < a.size(); ++i)
    {
        a[i] = rand() % 10;
    }
    a[a.size() - 1] = 1;
    double x = 0.5;
    auto start = clock();
    cout << evaluate(a, x) << endl;
    cout << clock() - start << endl;
    start = clock();
    cout << Horner(a, x) << endl;
    cout << clock() - start << endl;
    Tree *root = build(a);
    start = clock();
    cout << evaluate(root, x) << endl;
    cout << clock() - start << endl;
    start = clock();
    cout << fourier(a, x) << endl;
    cout << clock() - start << endl;
    return 0;
}
