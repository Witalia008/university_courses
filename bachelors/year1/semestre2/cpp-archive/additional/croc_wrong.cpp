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
//#include <assert.h>
using namespace std;

#define For(i,a,b,d) for (int i = (a); i != (b); i += d)
#define FORD(i,a,b) for (int i = (a); i >= b; i--)
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define REPD(i,n) for (int i = (n - 1); i >= 0; i--)
#define REP(i,n) for (int i = 0; i < (n); i++)
#define ALL(a) (a).begin(), (a).end()
#define CLR(a,x) memset(a,x,sizeof(a))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define Abs(a) ((a < 0) ? -(a) : a)
#define sqr(a) ((a)*(a))
#define pb push_back
#define mp make_pair
#define eps 10e-5
#define Inf 1000000000
#define Mi 1000000007
#define N 1005
#define K 32

typedef double ld;
typedef long long ll;
typedef int i;
typedef vector<i> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef pair<double, char> pdc;
typedef enum {heavy, light} lbl;

const int mx[4] = {1, -1, 0, 0};
const int my[4] = {0, 0, 1, -1};

inline ll gcd (ll a, ll b){ return (!b ? a : gcd (b, a % b)); }

const ld PI = 2 * acos(0.0);
const ll InfLL = ll(Inf) * ll(Inf);

int rand15() { return rand() % (1 << 15); }
int rand30() { return (rand15() << 15) + rand15(); }
int rand(int L, int R) { if (L > R) return R; return rand30() % (R - L + 1) + L; }
ld random(ld L, ld R) { return rand(ceil((L-eps)*100), floor((R+eps)*100)) / 100.0;}

//#define DEBUG

struct pt {
    ld x, y;
    pt () {}
    pt (ld _x, ld _y): x(_x), y(_y) {}
};

inline ld vd (pt a, pt b, pt c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

inline ld dist (pt a, pt b) {
    return sqrt (sqr (a.x - b.x) + sqr (a.y - b.y));
}

inline bool lay_on (pt o, pt a, pt b) {
    return Abs(dist (o, a) + dist (o, b) - dist (a, b)) <= eps;
}

inline bool intersect_proj (ld a, ld b, ld c, ld d) {
    if (a > b) swap (a, b);
    if (c > d) swap (c, d);
    return max (a, c) <= min (b, d);
}

inline bool intersects (pt a, pt b, pt c, pt d) {
    return intersect_proj(a.x, b.x, c.x, d.x) && intersect_proj(a.y, b.y, c.y, d.y) &&
            vd (a, b, c) * vd (a, b, d) <= 0 && vd (c, d, a) * vd (c, d, b) <= 0;
}

inline bool inside_polygon (pt poly[], int n, pt A) {
    int cnt_intersecs = 0;
    REP(i, n) {
        pt a = poly[i], b = poly[(i + 1) % n];
        //our point is on boundary
        if (lay_on(A, a, b))
            return true;
        //current segment lays on ray
        if (Abs(a.y - A.y) <= eps && Abs(b.y - A.y) <= eps) {
            if (min(a.x, b.x) > A.x) {
                pt prev = poly[(i - 1 + n) % n], next = poly[(i + 2) % n];
                if (max(prev.y, next.y) > A.y + eps && min (prev.y, next.y) < A.y + eps)
                    cnt_intersecs++;
            }
        } else {
            //holy intersection
            if (max(a.y, b.y) > A.y + eps && min(a.y, b.y) < A.y - eps){
                ld xx = a.x + (b.x - a.x) * ((A.y - a.y) / (b.y - a.y));
                if (xx > A.x)
                    cnt_intersecs++;
            } else if (Abs(a.y - A.y) <= eps && a.x > A.x) { //I-th point on the ray
                pt prev = poly[(i - 1 + n) % n];
                if (min(prev.y, b.y) < A.y && max(prev.y, b.y) > A.y)
                    cnt_intersecs++;
            }
        }
    }
    return (cnt_intersecs & 1);
}

vi adj[N];
queue<int> q;
ld d[N];
int p[N];
ld D[N][N];

ld dijkstra (int s, int t) {
    q.push(s);
    REP(i, N)
        d[i] = -1, p[i] = -1;
    d[s] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        REP(i, adj[v].size()) {
            int to = adj[v][i];
            if (d[to] < 0 || d[to] > d[v] + D[v][to]) {
                q.push(to);
                p[to] = v;
                d[to] = D[v][to] + d[v];
            }
        }
    }
    return d[t];
}

inline bool cw (pt a, pt b, pt c) {
    return vd(a, b, c) < 0;
}

inline bool ccw (pt a, pt b, pt c) {
     return vd(a, b, c) > 0;
}

bool poly_cw (pt poly[], int n) {
    int res = 0;
    for (int i = 0; i < n; i++)
        if (poly[i].y < poly[res].y || poly[i].y == poly[res].y && poly[i].x > poly[res].x)
            res = i;
    return cw(poly[res], poly[(res + 1) % n], poly[(res - 1 + n) % n]);
}

int numb[N];
int n, s, f;
pt A[N];
vi ans;

//#define DEBUG_MODE
//#define ONLINE_JUDGE
int main ()
{
    std::ios_base::sync_with_stdio(0);
    #ifndef ONLINE_JUDGE
        freopen ("input.txt", "r", stdin);
        freopen ("output.txt", "wb", stdout);
    #endif
    cin >> n;
    REP(i, n) {
        cin >> A[i].x >> A[i].y;
        numb[i] = i;
    }
    cin >> s >> f;
    if (poly_cw(A, n)) {
        reverse(A, A + n);
        for (int i = 0; i < n; i++)
            numb[i] = n - 1 - i;
        s = numb[s];
        f = numb[f];
    }
    REP(i, n)
    {
        REP(j, i)
        {
            bool good = true;
            REP(k, n)
                if (intersects(A[i], A[j], A[k], A[(k + 1) % n]))
                    if (i != k && i != (k + 1) % n && j != k && j != (k + 1) % n){
                        good = false;
                        break;
                    }
            if (good && i != j + 1) {
                //good &= inside_polygon (A, n, pt((A[i].x + A[j].x) / 2, (A[i].y + A[j].y) / 2));
                if (cw(A[i], A[(i + 1) % n], A[j]) || ccw(A[i], A[(i - 1 + n) % n], A[j]))
                    good = false;
                if (cw(A[j], A[(j + 1) % n], A[i]) || ccw(A[j], A[(j - 1 + n) % n], A[i]))
                    good = false;
            }

            if (good) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
            D[i][j] = D[j][i] = dist (A[i], A[j]);
        }
        adj[i].push_back((i + 1) % n);
        adj[(i + 1) % n].push_back(i);
    }
    cout << dijkstra (s, f) << endl;
    int l = f;
    while (l != -1) {
        ans.push_back(numb[l]);
        l = p[l];
    }
    REPD(i, ans.size())
    {
        if (i != ans.size() - 1)
            cout << " ";
        cout << ans[i];
    }
    cout << endl;
    return 0;
}
