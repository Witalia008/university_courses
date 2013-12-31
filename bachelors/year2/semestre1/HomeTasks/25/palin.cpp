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

/**
Function, that finds palindrome string, that can be received from given by minimum deletions of chars.
*/
string getPalin(const string &s) {
    int n = s.size();
    vector<vector<int>> F(n);
    for (auto &i : F) i.assign(n, -1);
    /*
    Function F(i, j) keep minimum number of characters needed to delete from substring s[i..j]
    to make it palindrom. answer for s will be in s[0..s.len-1]
    F(i, j) = F(i + 1, j - 1) if s[i] == s[j]  -  if edge characters are the same, we dont need to delete them.
    F(i, j) = 1 + min(F(i + 1, j), F(i, j - 1)) - s[i] != s[j]. If two edge characters are not the same,
    we try to delete left or right and choose the cheapest variant.
    For lenght l of substr answer for lengths 0..l-1 should be calculated.
    assume F[i][i] = 0
    */
    for (int len = 1; len <= n; ++len) {    //iterate length of substring
        for (int i = 0; i + len - 1 < n; ++i) { //iterate left index of substring
            int j = i + len - 1;                //calculate appropriate right index
            if (s[i] == s[j])
                F[i][j] = (i + 1 < j ? F[i + 1][j - 1] : 0);
            else
                F[i][j] = 1 + min(F[i + 1][j], F[i][j - 1]);
        }
    }
    /*
    Here recover answer. Each half of palindrome separately.
    start from 0..len(s)-1. Then if s[l] == s[r], so those two chars are in answer - add them to both halves.
    odd will keep if this palindrome has odd length
    if s[l] != s[r], then we delete char at l or ar r and move to appropriate substring.
    */
    string res = "";
    int l = 0, r = n - 1;
    bool odd = false;
    while (l <= r) {
        if (s[l] == s[r]) {
            res += s[l];
            if (l == r)
                odd = true;
            ++l; --r;
        } else {
            if (F[l][r] - 1 == F[l + 1][r])    //it's better to delete left char of substr
                ++l;
            else --r;    //it's better to del right
        }
    }
    string x = res;
    reverse(ALL(x));
    if (odd) x.erase(0, 1);//if string has odd len then middle char was added twice - delete it
    return res + x;
}

//#define ONLINE_JUDGE
int main () {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    string s;
    cin >> s;
    cout << getPalin(s) << endl;
    return 0;
}