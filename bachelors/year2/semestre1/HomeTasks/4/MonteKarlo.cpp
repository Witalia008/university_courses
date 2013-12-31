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

double random() {
    return (double) rand() / RAND_MAX;
}

double integrate(vector<pair<double, double>> lim, double func(vector<double>&), bool pred(vector<double>&)) {
    double mM = 1;
    for (auto i : lim)
        mM *= i.second - i.first;
    double ans = 0;
    srand(time(NULL));
    REP(i, N) {
        vector<double> X(lim.size());
        REP(j, X.size()) {
            X[j] = lim[j].first + (lim[j].second - lim[j].first) * random();
        }
        ans += func(X) * pred(X);
    }
    return mM * ans / N;
}

//#define ONLINE_JUDGE
int main () {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    vector<pair<double, double>> lims;
    lims.push_back(make_pair(0.5, 1));
    lims.push_back(make_pair(0, 1));
    cout << integrate(lims, [](vector<double>& x) -> double {
        return x[0] * x[0] + x[1] * x[1];
    }, [](vector<double>& x) -> bool {
        return x[1] <= x[0] * 2 - 1;
    }) << endl;
    return 0;
}