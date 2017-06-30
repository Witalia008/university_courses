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
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

//const int mx[4] = { 1, 0, -1, 0 };
//const int my[4] = { 0, 1, 0, -1 };

const int Inf = 1000000000;
const int Mi = 1000000007;
const int N = 500005;
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

ll binary_gcd(ll a, ll b)
{
    ll d_even = 1;
    while (a && b)
    {
        if (!(a & 1) && !(b & 1))
        {
            a >>= 1;
            b >>= 1;
            d_even <<= 1;
        }
        else if (!(a & 1))
        {
            a >>= 1;
        }
        else if (!(b & 1))
        {
            b >>= 1;
        }
        else
        {
            if (a > b)
            {
                a = (a - b) >> 1;
            }
            else
            {
                b = (b - a) >> 1;
            }
        }
    }
    return max(a, b) * d_even;
}

ll gcd_it(ll a, ll b)
{
    while (b)
    {
        a %= b;
        swap(a, b);
    }
    return a;
}

ll gcd_ext(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = gcd_ext(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

//#define ONLINE_JUDGE
int main()
{
    std::ios_base::sync_with_stdio(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ll a, b;
    cin >> a >> b;
    cout << binary_gcd(a, b) << endl;
    ll x, y;
    gcd_ext(a, b, x, y);
    cout << x << " " << y << endl;

    auto st = clock();
    for (int i = 0; i < 1e7; ++i)
    {
        ll a = rand64(), b = rand64();
        binary_gcd(a, b);
    }
    auto f = clock();
    cout << "Binary GCD: " << (f - st) << "ms" << endl;
    st = clock();
    for (int i = 0; i < 1e7; ++i)
    {
        ll a = rand64(), b = rand64();
        gcd_it(a, b);
    }
    f = clock();
    cout << "GCD: " << (f - st) << "ms" << endl;
    return 0;
}