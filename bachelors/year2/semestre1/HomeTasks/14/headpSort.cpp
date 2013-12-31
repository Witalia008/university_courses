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

void shiftUp(int i, vector<int> &a) {
    if (!i) return;
    if (a[i] > a[(i - 1) / 2]) {
        swap(a[i], a[(i - 1) / 2]);
        shiftUp((i - 1) / 2, a);
    }
}

void shiftDown(int i, int n, vector<int> &a) {
    if (i * 2 + 1 < n) {
        int k = i;
        if (a[i * 2 + 1] > a[i]) k = i * 2 + 1;
        if (i * 2 + 2 < n && a[i * 2 + 2] > a[k])
            k = i * 2 + 2;
        if (k == i)
            return;
        swap(a[i], a[k]);
        shiftDown(k, n, a);
    }
}

void heapSort(vector<int> &a) {
    for (int i = 0; i < a.size(); ++i)
        shiftUp(i, a);
    int n = a.size();
    for (int i = n - 1; i > 0; --i) {
        swap(a[i], a[0]);
        shiftDown(0, --n, a);
    }
}

//#define ONLINE_JUDGE
int main () {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    vector<int> a(100);
    generate(ALL(a), []() { return rand() % 100; });
    copy(ALL(a), ostream_iterator<int>(cout, " ")); cout << endl;
    heapSort(a);
    copy(ALL(a), ostream_iterator<int>(cout, " ")); cout << endl;
    return 0;
}