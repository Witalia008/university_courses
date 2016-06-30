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

const int mx[4] = {1, 0, -1, 0};
const int my[4] = {0, 1, 0, -1};

const int Inf = 1000000000;
const int Mi = 1000000007;
const int N = 32005;
const int K = 20;
const ld eps = 1e-5;
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

struct Point
{
    double x, y;
};

struct Rect
{
    Point ldown, rup;
};

enum NodeType
{
    VERTICAL,
    HORIZONTAL
};

struct Tree
{
    NodeType t;
    Point p;
    Rect r;
    Tree *lefts, *rights;
};

Tree *build(vector<Point> &a, int l, int r,
            NodeType t = VERTICAL, Rect rect = {{-Inf, -Inf}, {Inf, Inf}})
{
    if (l > r)
    {
        return nullptr;
    }

    int mid = (r + l) >> 1;
    nth_element(a.begin() + l, a.begin() + mid, a.begin() + r + 1,
                [t](Point a, Point b) -> bool {
                    if (t == VERTICAL)
                        return a.x < b.x;
                    else
                        return a.y < b.y;
                });

    Tree *cur = new Tree();
    cur->r = rect;
    cur->p = a[mid];
    cur->t = t;
    if (t == VERTICAL)
    {
        cur->lefts = build(a, l, mid - 1, HORIZONTAL, {rect.ldown, {cur->p.x, rect.rup.y}});
        cur->rights = build(a, mid + 1, r, HORIZONTAL, {{cur->p.x, rect.ldown.y}, rect.rup});
    }
    else
    {
        cur->lefts = build(a, l, mid - 1, VERTICAL, {rect.ldown, {rect.rup.x, cur->p.y}});
        cur->rights = build(a, mid + 1, r, VERTICAL, {{rect.ldown.x, cur->p.y}, rect.rup});
    }
    return cur;
}

vector<Point> get(Tree *v, Rect r)
{
    if (v == nullptr ||
        r.ldown.x > r.rup.x + eps ||
        r.ldown.y > r.rup.y + eps)
    {
        return {};
    }
    vector<Point> left, right;

    if (v->t == VERTICAL)
    {
        left = get(v->lefts, {r.ldown, {v->p.x, r.rup.y}});
        right = get(v->rights, {{v->p.x, r.ldown.y}, r.rup});
    }
    else
    {
        left = get(v->lefts, {r.ldown, {r.rup.x, v->p.y}});
        right = get(v->rights, {{r.ldown.x, v->p.y}, r.rup});
    }

    vector<Point> res = left;
    res.insert(res.end(), right.begin(), right.end());
    if (v->p.x >= r.ldown.x - eps && v->p.x <= r.rup.x + eps &&
        v->p.y >= r.ldown.y - eps && v->p.y <= r.rup.y + eps)
    {
        res.push_back(v->p);
    }
    return res;
}

//#define ONLINE_JUDGE
int main()
{
    std::ios_base::sync_with_stdio(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n;
    vector<Point> a;
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i].x >> a[i].y;
    }
    Tree *root = build(a, 0, n - 1);

    Rect d;
    cin >> d.ldown.x >> d.ldown.y;
    cin >> d.rup.x >> d.rup.y;

    auto b = get(root, d);
    for (auto x : b)
    {
        cout << x.x << " " << x.y << endl;
    }
    return 0;
}
/*
8
30 60
50 40
0 30
15 25
70 30
55 20
50 10
20 0
10 15 65 50
*/