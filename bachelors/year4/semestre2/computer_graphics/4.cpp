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

double Abs(double a)
{
    return a < 0 ? -a : a;
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

double dist(Point a, Point b)
{
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

vector<Point> left_convex_hull(vector<Point> s, Point pl, Point pr)
{
    if (s.size() <= 2)
    {
        return s;
    }
    int ph = -1;
    double phdist = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        double A = pr.y - pl.y;
        double B = pl.x - pr.x;
        double C = pr.x * pl.y - pr.y * pl.x;
        double dist = Abs(A * s[i].x + B * s[i].y + C) / sqrt(A * A + B * B);
        if (ph == -1 || dist > phdist)
        {
            phdist = dist;
            ph = i;
        }
    }
    Point phh = s[ph];
    vector<Point> Sl = {pl, phh}, Sr = {phh, pr};
    for (auto x : s)
    {
        if (ccw(pl, phh, x))
        {
            Sl.push_back(x);
        }
        else if (ccw(phh, pr, x))
        {
            Sr.push_back(x);
        }
    }
    vector<Point> l = left_convex_hull(Sl, pl, phh);
    vector<Point> r = left_convex_hull(Sr, phh, pr);
    for (int i = 1; i < r.size(); ++i)
    {
        l.push_back(r[i]);
    }
    return l;
}

vector<Point> convex_hull(vector<Point> a)
{
    Point pl = a[0], pr = a[0];
    for (int i = 0; i < a.size(); ++i)
    {
        if (a[i].x < pl.x)
        {
            pl = a[i];
        }
        if (a[i].x > pr.x)
        {
            pr = a[i];
        }
    }
    vector<Point> Sl = {pl, pr}, Sr = {pl, pr};
    for (auto x : a)
    {
        if (ccw(pl, pr, x))
        {
            Sl.push_back(x);
        }
        if (cw(pl, pr, x))
        {
            Sr.push_back(x);
        }
    }
    vector<Point> up = left_convex_hull(Sl, pl, pr);
    vector<Point> down = left_convex_hull(Sr, pr, pl);
    for (int i = 1; i + 1 < down.size(); ++i)
    {
        up.push_back(down[i]);
    }
    return up;
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
    vector<Point> hull = convex_hull(pts);
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