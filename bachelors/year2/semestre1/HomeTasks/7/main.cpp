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
#include <chrono>

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

#include "Queue.h"

template<class T>
void testSort(vector<T> &A, void sorter(Queue<T>&), string name) {
    using namespace std::chrono;
    Queue<T> a(A);
    cout << "Testing " + name << endl;
    auto start = high_resolution_clock::now();
    sorter(a);
    auto finish = high_resolution_clock::now();
    cout << fixed << setprecision(3) << static_cast<double>(duration_cast<milliseconds>(finish - start).count()) / 1000 << "ms" << endl;
}

#define ONLINE_JUDGE
int main () {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<int> x(n);
    generate(ALL(x), rand);
    cout << "\nrandom array\n";
    testSort<int>(x, quickSort, "quick");
    testSort<int>(x, insertionSort, "insertion");
    
    sort(ALL(x));
    cout << "\nsorted array\n";
    testSort<int>(x, quickSort, "quick");
    testSort<int>(x, insertionSort, "insertion");

    reverse(ALL(x));
    cout << "\nreversed array\n";

    testSort<int>(x, quickSort, "quick");
    testSort<int>(x, insertionSort, "insertion");

    system("pause");
    return 0;
}