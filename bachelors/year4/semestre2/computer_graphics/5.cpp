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

int get_side_point(vector<Point> pts, bool cmp(Point, Point))
{
    int idx = 0;
    for (int i = 1; i < pts.size(); ++i)
    {
        if (cmp(pts[i], pts[idx]))
        {
            idx = i;
        }
    }
    return idx;
}

bool cw(Point a, Point b, Point c)
{
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) < 0;
}

bool ccw(Point a, Point b, Point c)
{
    return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y) > 0;
}

vector<Point> unite(vector<Point> left, vector<Point> right)
{
    int ln = left.size(), rn = right.size();
    int a = get_side_point(left, [](Point a, Point b) -> bool { return a.x > b.x; });
    int b = get_side_point(right, [](Point a, Point b) -> bool { return a.x < b.x; });
    int lup = a, ldown = a;
    int rup = b, rdown = b;

    // find upper tangent
    for (;;)
    {
        if (ccw(left[(lup + ln - 1) % ln], left[lup], right[rup]))
        {
            lup = (lup + ln - 1) % ln;
        }
        else if (cw(right[(rup + 1) % rn], right[rup], left[lup]))
        {
            rup = (rup + 1) % rn;
        }
        else
        {
            break;
        }
    }
    // find lower tangent
    for (;;)
    {
        if (cw(left[(ldown + 1) % ln], left[ldown], right[rdown]))
        {
            ldown = (ldown + 1) % ln;
        }
        else if (ccw(right[(rdown + rn - 1) % rn], right[rdown], left[ldown]))
        {
            rdown = (rdown + rn - 1) % rn;
        }
        else
        {
            break;
        }
    }
    vector<Point> res;
    for (;;)
    {
        res.push_back(left[ldown]);
        if (ldown == lup)
        {
            break;
        }
        ldown = (ldown + 1) % ln;
    }
    for (;;)
    {
        res.push_back(right[rup]);
        if (rup == rdown)
        {
            break;
        }
        rup = (rup + 1) % rn;
    }
    return res;
}

double dist(Point a, Point b)
{
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}
double Abs(double a)
{
    return a < 0 ? -a : a;
}

vector<Point> convex_hull_slow(vector<Point> a)
{
    vector<Point> res;
    int st = 0;
    int n = a.size();
    for (int i = 1; i < n; ++i)
    {
        if (a[i].y < a[st].y || Abs(a[i].y - a[st].y) < eps && a[i].x < a[st].x)
        {
            st = i;
        }
    }
    int prev = st;
    Point p = a[prev], q;
    q = p;
    q.x -= 1;
    for (;;)
    {
        res.push_back(p);
        int nxt = -1;
        double ang;
        for (int i = 0; i < n; ++i)
        {
            if (i != prev)
            {
                double da = dist(q, p);
                double db = dist(p, a[i]);
                double dc = dist(q, a[i]);
                double angle = M_PI - acos((da * da + db * db - dc * dc) / (2 * da * db));
                if (nxt == -1 || ang > angle)
                {
                    nxt = i;
                    ang = angle;
                }
            }
        }
        if (nxt == st)
        {
            break;
        }
        q = p;
        p = a[nxt];
        prev = nxt;
    }
    reverse(res.begin(), res.end());
    return res;
}

vector<Point> convex_hull(vector<Point> a)
{
    int n = a.size();
    if (n < 5)
    {
        return convex_hull_slow(a);
    }
    vector<Point> l, r;
    for (int i = 0; i < n; ++i)
    {
        (i < n / 2 ? l : r).push_back(a[i]);
    }
    return unite(convex_hull(l), convex_hull(r));
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
    sort(pts.begin(), pts.end(), [](Point a, Point b) -> bool { return a.x < b.x; });
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