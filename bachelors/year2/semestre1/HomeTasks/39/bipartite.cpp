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
#include <cassert>

using namespace std;

#define For(i,a,b,d) for (int i = (a); i != (b); i += d)
#define FORD(i,a,b) for (int i = (a); i >= b; i--)
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define REPD(i,n) for (int i = (n - 1); i >= 0; i--)
#define REP(i,n) for (int i = 0; i < (n); i++)
#define ALL(a) (a).begin(), (a).end()
#define CLR(a,x) memset(a,x,sizeof(a))
#define debug(x) cout << #x << "=" << x << endl;
#define pb push_back
#define mp make_pair

typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;

const int mx[4] = {1, -1, 0, 0};
const int my[4] = {0, 0, 1, -1};

const int Inf = 2000000000;
const int Mi = 1000000009;
const int N = 205;
const int K = 3005;
const ld eps = 10e-6;
const ld PI = 2 * acos(0.0);
const ll InfLL = ll(Inf) * ll(Inf);

ll gcd(ll a, ll b) {
    if (!b) return a;
    return gcd(b, a % b);
}

ll lcm(ll a, ll b) {
    return (a / gcd(a, b)) * b;
}

int n;
vector<vector<int>> A;
vector<int> comp;

void dfs(int v, int curPart) {
    comp[v] = curPart;
    for (int to = 0; to < n; ++to) 
        if (A[v][to]) {
            if (comp[to] == 0)
                dfs(to, 3 - curPart);
            else {
                if (comp[to] == comp[v]) {
                    cout << "No partition\n";
                    exit(0);
                }
            }
        }
}

//#define ONLINE_JUDGE
int main () {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin >> n;
    A.resize(n);
    for_each(ALL(A), [](vector<int>&cur) {
        cur.resize(n);
        for(auto&i : cur)
            cin >> i;
    });
    comp.assign(n, 0);
    dfs(0, 1);
    copy(ALL(comp), ostream_iterator<int>(cout, " "));
    return 0;
}