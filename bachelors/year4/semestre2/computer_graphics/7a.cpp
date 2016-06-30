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
const int N = 50005;
const int K = 20;
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

struct Point
{
    double x, y;
};

bool cw(Point a, Point b, Point c)
{
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) < 0;
}

bool ccw(Point a, Point b, Point c)
{
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) > 0;
}

vector<Point> convex_hull(vector<Point> a)
{
    if (a.size() == 1)
    {
        return a;
    }
    // not needed for hull approximation
    //sort(a.begin(), a.end(), [](Point a, Point b) -> bool { return a.x < b.x; });
    Point p1 = a[0], p2 = a.back();
    vector<Point> up = {p1}, down = {p1};
    for (int i = 1; i < a.size(); ++i)
    {
        if (i == a.size() - 1 || ccw(p1, p2, a[i]))
        {
            while (up.size() >= 2 && !cw(up[up.size() - 2], up.back(), a[i]))
            {
                up.pop_back();
            }
            up.push_back(a[i]);
        }
        if (i == a.size() - 1 || cw(p1, p2, a[i]))
        {
            while (down.size() >= 2 && !ccw(down[down.size() - 2], down.back(), a[i]))
            {
                down.pop_back();
            }
            down.push_back(a[i]);
        }
    }

    for (int i = down.size() - 2; i > 0; --i)
    {
        up.push_back(down[i]);
    }
    return up;
}

vector<Point> hull_approx(vector<Point> a)
{
    int minx = 0, maxx = 0;
    for (int i = 1; i < a.size(); ++i)
    {
        if (a[i].x < a[minx].x)
        {
            minx = i;
        }
        if (a[i].x > a[maxx].x)
        {
            maxx = i;
        }
    }
    int k = a.size() / 3;
    vector<pii> ints(k, make_pair(-1, -1));
    for (int i = 0; i < a.size(); ++i)
    {
        int idx = k * (a[i].x - a[minx].x) / (a[maxx].x - a[minx].x);
        idx = min(idx, k - 1);
        if (ints[idx].second == -1 || a[i].y > a[ints[idx].second].y)
        {
            ints[idx].second = i;
        }
        if (ints[idx].first == -1 || a[i].y < a[ints[idx].first].y)
        {
            ints[idx].first = i;
        }
    }
    vector<Point> s = {a[minx]};
    set<int> bad = {-1, minx, maxx};
    for (int i = 0; i < k; ++i)
    {
        bool f1 = bad.find(ints[i].first) == bad.end();
        bool f2 = bad.find(ints[i].second) == bad.end();
        if (f1)
        {
            s.push_back(a[ints[i].first]);
        }
        if (f2)
        {
            s.push_back(a[ints[i].second]);
        }
        if (f1 && f2)
        {
            if (s[s.size() - 2].x > s.back().x)
            {
                swap(s[s.size() - 1], s[s.size() - 2]);
            }
        }
    }
    s.push_back(a[maxx]);
    return convex_hull(s);
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
    cin >> n;
    vector<Point> pts;
    pts.resize(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> pts[i].x >> pts[i].y;
    }
    vector<Point> hull = hull_approx(pts);
    cout << hull.size() << endl;
    for (int i = 0; i < hull.size(); ++i)
    {
        cout << hull[i].x << " " << hull[i].y << endl;
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
*/