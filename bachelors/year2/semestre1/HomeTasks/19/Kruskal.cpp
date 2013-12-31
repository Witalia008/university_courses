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

int getDsu(int v, vector<int> &dsu) {
    if (v == dsu[v])
        return v;
    return dsu[v] = getDsu(dsu[v], dsu);
}

bool dsuUnion(int u, int v, vector<int> &dsu) {
    /* get roots of sets of both vertices */
    u = getDsu(u, dsu);
    v = getDsu(v, dsu);
    if (u == v) return false;//are in same set
    if (rand() & 1)        //no - union
        swap(u, v);
    dsu[u] = v;
    return true;
}

void kruskal(int n, vector<pair<int, pair<int, int>>> &ribs) {    //vector of ribs, each rib - (weight, (source vertex, destination) )
    vector<int> dsu(n);
    generate(ALL(dsu), []() { static int n = 0; return n++; });    //initially dsu = seq(0, 1, 2...) - means, that each vertex in it's own set
    sort(ALL(ribs));
    int ans = 0;
    for (auto &i : ribs) {
        if (dsuUnion(i.second.second, i.second.first, dsu)) {        //try to union source and destination of current vertex (dsu - set itself)
            cout << i.second.first << " " << i.second.second << endl;    //if sucessfully - add rib to answer
            ans += i.first;
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
    vector<pair<int, pair<int, int>>> ribs;
    REP(i, m) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        ribs.push_back(make_pair(w, make_pair(u, v)));
    }
    kruskal(n, ribs);
    return 0;
}