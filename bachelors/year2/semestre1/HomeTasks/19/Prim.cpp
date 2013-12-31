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

void prima(int n, vector<vector<pair<int, int>>> &adj) {        //adj - for each vertex holds vector of adjacent vertices as(destination, weight) 
    vector<int> dst(n, Inf);        //destination from current tree to each vertex
    vector<int> par(n, -1);            //parent of vertex (means vertex, from which goes edge with length dst[i])
    vector<bool> used(n, false);    //if vertex is in subtree
    dst[0] = 0;
    int ans = 0;
    for (int step = 0; step < n; ++step) {
        int k = -1;            //will keep vertex with minimum distance from tree
        for (int i = 0; i < n; ++i)
            if (!used[i] && (k == -1 || dst[k] > dst[i]))        //if no found vertex or current has less length that already found
                k = i;        //replace minimum
        if (k == -1)    //if not found - graph is not connected - find first unused.
            for (k = 0; used[k]; ++k);
        if (k == -1)
            return;
        if (par[k] != -1)
            cout << par[k] << " " << k << endl;        //edge par[k] - k add to answer 
        ans += dst[k];
        used[k] = true;        //add k to subtree
        for (const auto &i : adj[k])        //for all adjective vertices
            if (dst[i.first] > i.second) {    //update minimal distance to them
                dst[i.first] = i.second;
                par[i.first] = k;
            }
    }
    cout << "Total:\n" << ans << endl;
}

//#define ONLINE_JUDGE
int main () {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj;
    adj.resize(n);
    REP(i, m) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
    prima(n, adj);
    return 0;
}