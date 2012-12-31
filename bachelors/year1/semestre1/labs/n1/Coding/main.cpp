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
using namespace std;

#define For(i,a,b,d) for (int i = (a); i != (b); i += d)
#define FORD(i,a,b) for (int i = (a); i >= b; i--)
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define REPD(i,n) for (int i = (n - 1); i >= 0; i--)
#define REP(i,n) for (int i = 0; i < (n); i++)
#define CLR(a,x) memset(a,x,sizeof(a))
#define pb push_back
#define mp make_pair
#define eps 10e-7
#define InfL 10000000000000000LL
#define Inf 2000010000
#define Mi 100000000
#define N 1000015
#define K 105
//#define debug

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

inline ll Abs (ll x) { return x < 0 ? -x : x;}
inline ll sqr (ll a) { return a*a; }
inline ll gcd (ll a, ll b) { return (!b ? a : gcd (b, a % b)); }
inline ll minn (ll a, ll b) { return a < b ? a : b; }
inline ll maxx (ll a, ll b) { return a > b ? a : b; }

int n, en, a, b, m;
int A[N], d[N];

int bin_srch (int wh)
{
    if (!en) return 0;
    int l = 0, r = en - 1;
    while (l < r - 1)
    {
        int mid = (l + r) >> 1;
        if (d[mid] <= wh)
            l = mid;
        else
            r = mid;
    }
    if (d[l] >= wh) return l;
    if (d[r] >= wh) return r;
    return r + 1;
}

//#define ONLINE_JUDGE
int main ()
{
    #ifndef ONLINE_JUDGE
        freopen ("input.txt", "r", stdin);
        freopen ("output.txt", "w", stdout);
    #endif
    n = -1;
    scanf ("%d%d%d%d", &a, &b, &m, &n);
    while (n != -1)
    {
        en = 0;
        A[0] = a + b; A[1] = a - b;
        n++;
        REP(i, n)
        {
            if (i > 1)
                A[i] = int((ll(a) * A[i - 2] + ll(b) * A[i - 1]) % m);
            int cur = bin_srch (A[i]);
            if (cur == en) en++;
            d[cur] = A[i];
        }
        printf ("%d\n", en);
        n = -1;
        scanf ("%d%d%d%d", &a, &b, &m, &n);
    }
    return 0;
}
