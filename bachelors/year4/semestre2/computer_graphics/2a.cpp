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

double Abs(double a)
{
    return a < 0 ? -a : a;
}

struct Point
{
    double x, y;
};

struct Segm
{
    Point fr, to;
    int e_n;
};

bool cw(Point a, Point b, Point c)
{
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) < 0;
}

bool ccw(Point a, Point b, Point c)
{
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) > 0;
}

int bin_srch(vector<double> a, double x)
{
    int l = 0, r = a.size() - 1;
    while (r - l > 1)
    {
        int mid = (l + r) >> 1;
        if (a[mid] <= x + eps)
        {
            l = mid;
        }
        else
        {
            r = mid;
        }
    }
    if (a[r] <= x + eps)
    {
        return r;
    }
    return l;
}

int bin_srch_s(vector<Segm> a, Point x)
{
    int l = 0, r = a.size() - 1;
    while (r - l > 1)
    {
        int mid = (r + l) >> 1;
        if (!ccw(a[mid].fr, a[mid].to, x))
        {
            l = mid;
        }
        else
        {
            r = mid;
        }
    }
    if (!ccw(a[r].fr, a[r].to, x))
    {
        return r;
    }
    return l;
}

int n, m, k;
vector<Point> pts;
vector<pii> edges;
vector<double> ys;
vector<vector<Segm>> s;

//#define ONLINE_JUDGE
int main()
{
    std::ios_base::sync_with_stdio(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin >> n;
    pts.resize(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> pts[i].x >> pts[i].y;
        ys.push_back(pts[i].y);
    }
    cin >> m;
    edges.resize(m);
    for (int i = 0; i < m; ++i)
    {
        cin >> edges[i].first >> edges[i].second;
    }

    // get y coords of stripes
    sort(ys.begin(), ys.end());
    auto it = unique(ys.begin(), ys.end(), [](double a, double b) -> bool {
        return Abs(b - a) < eps;
    });
    ys.resize(distance(ys.begin(), it));

    // fill up stripes
    s.resize(ys.size() - 1);
    for (int i = 0; i < m; ++i)
    {
        Point fr = pts[edges[i].first], to = pts[edges[i].second];
        if (fr.y > to.y)
        {
            swap(fr, to);
        }
        int pos = bin_srch(ys, fr.y) + 1;
        while (pos < ys.size() && ys[pos] <= to.y + eps)
        {
            Point cur;
            cur.y = ys[pos];
            cur.x = (ys[pos] - ys[pos - 1]) / (to.y - fr.y) * (to.x - fr.x) + fr.x;
            s[pos - 1].push_back(Segm{fr, cur, i});
            fr = cur;
            ++pos;
        }
    }
    // sort segments in stripes
    for (int i = 0; i < s.size(); ++i)
    {
        sort(s[i].begin(), s[i].end(), [](Segm a, Segm b) -> bool {
            if (Abs(a.fr.x - b.fr.x) < eps)
            {
                return a.to.x < b.to.x;
            }
            return a.fr.x < b.fr.x;
        });
    }

    // localize point
    Point pt;
    cin >> pt.x >> pt.y;
    int pos = bin_srch(ys, pt.y);
    int pos_s = bin_srch_s(s[pos], pt);
    cout << s[pos][pos_s].e_n << endl;
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
7
0 1
1 2
2 3
3 4
4 5
5 6
6 7

70 27
*/