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
#define PI 2*acos(0.0)
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
typedef ld us_t;

const int mx[4] = {1, -1, 0, 0};
const int my[4] = {0, 0, 1, -1};

inline us_t Abs (us_t x) { return x < 0 ? -x : x;}
inline us_t sqr (us_t a) { return a*a; }
inline ll gcd (ll a, ll b) { return (!b ? a : gcd (b, a % b)); }
inline us_t minn (us_t a, us_t b) { return a < b ? a : b; }
inline us_t maxx (us_t a, us_t b) { return a > b ? a : b; }
