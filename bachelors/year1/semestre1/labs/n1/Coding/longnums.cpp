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
#define SET(a,x,f,s) for (int i = f; i <= s; i++) a[i] = x
#define pb push_back
#define mp make_pair
#define eps 10e-7
#define InfL 10000000000000000LL
#define Inf 2000010000
#define Mi 1000000007
#define N 1015
#define K 15
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

#define tlong(A) int * A = new int[N + 4] + 4;
#define base -4
#define len -3
#define sign -2
#define dot -1

int * StrToL (string s)
{
    tlong(a);
    SET(a, 0, -4, N - 1);
    a[base] = 10;
    a[sign] = (s[0] == '-' ? '-' : '+');
    if (s[0] == '-' || s[0] == '+') s.erase(0, 1);
    REPD(i, s.length())
    {
        if (s[i] == '.')
        {
            a[dot] = s.length() - i - 1;
            s.erase(i, 1);
        }
        if (s[i] >= '0' && s[i] <= '9')
            a[s.length() - i - 1] = s[i] - '0';
        if (s[i] >= 'A' && s[i] <= 'Z')
            a[s.length() - i - 1] = s[i] - 'A';
    }
    a[len] = s.length();
    return a;
}

int * inputL(ifstream &inp)
{
    string s;
    inp >> s;
    return StrToL(s);
}

void outputL (int * a, ofstream &f)
{
    if (a[sign] == '-') f << '-';
    REPD(i, a[len])
    {
        if (i == a[dot] - 1) f << '.';
        if (a[i] < 10) f << a[i];
        else f << a[i] + 'A';
    }
    f << endl;
}

int lenL (int * a)
{
    int i;
    for (i = N - 1; i > 0 && a[i] == 0; i--);
    return i + 1;
}

bool comp_0 (int * a)
{
    REP(i, a[len])
        if (a[i])
            return false;
    return true;
}

void shift (int * a, int k)
{
    if (!k) return;
    if (k > 0){
        REPD(i, a[len])
            a[i + k] = a[i], a[i] = 0;
    } else {
        REP(i, a[len])
        {
            if (i + k >= 0)
                a[i + k] = a[i];
            a[i] = 0;
        }
    }
    a[dot] = max (a[dot] + k, 0);
    a[len] = max (a[len] + k, 1);
    if (comp_0(a)) a[sign] = '+';
}

void SetPrecision(int * a, int pr)
{
    if (pr >= 0)
        shift(a, pr - a[dot]);
}

int comp_abs (int * a, int * b)
{
    int da = a[dot], db = b[dot];
    if (a[dot] > b[dot])
        shift(b, a[dot] - b[dot]);
    else
        shift(a, b[dot] - a[dot]);
    int ans = 0;
    int i;
    for (i = a[len]; i && a[i] == b[i]; i--);
    if (a[i] < b[i]) ans = -1;
    if (a[i] > b[i]) ans = 1;
    SetPrecision(a, da);
    SetPrecision(b, db);
    return ans;
}

int comp (int * a, int * b)
{
    if (a[sign] != b[sign])
        return a[sign] == '-' ? -1 : 1;
    return (a[sign] == '-' ? -1 : 1) * comp_abs(a, b);
}

int * sumL_abs (int * a, int * b)
{
    int da = dot[a], db = dot[b];
    tlong(res);
    SET(res, 0, 0, N - 1);
    int p = 0;
    shift(a, max (b[dot] - a[dot], 0));
    shift(b, max (a[dot] - b[dot], 0));
    for (int i = 0; i < max (a[len], b[len]) || p; i++)
    {
        res[i] = a[i] + b[i] + p;
        p = res[i] >= a[base];
        if (p) res[i] -= a[base];
    }
    res[base] = a[base];
    res[len] = lenL(res);
    res[sign] = a[sign];
    res[dot] = a[dot];
    SetPrecision(a, da);
    SetPrecision(b, db);
    return res;
}

int * subL_abs (int * a, int * b)
{
    int da = a[dot], db = b[dot];
    tlong(res);
    SET(res, 0, 0, N - 1);
    int z = 0;
    shift(a, max (b[dot] - a[dot], 0));
    shift(b, max (a[dot] - b[dot], 0));
    REP(i, a[len])
    {
        res[i] = a[i] - b[i] - z;
        z = res[i] < 0;
        if (z) res[i] += a[base];
    }
    res[base] = a[base];
    res[len] = lenL(res);
    res[sign] = a[sign];
    res[dot] = a[dot];
    SetPrecision(a, da);
    SetPrecision(b, db);
    return res;
}

int * Add (int * a, int * b)
{
    tlong(res);
    SET(res, 0, 0, N - 1);
    if (a[sign] == b[sign])
        res = sumL_abs(a, b);
    else {
        if (comp_abs(a, b) >= 0)
            res = subL_abs(a, b);
        else
            res = subL_abs(b, a);
    }
    return res;
}

int * Sub (int * a, int * b)
{
    tlong(res);
    SET(res, 0, 0, N - 1);
    b[sign] = (b[sign] == '-' ? '+' : '-');
    res = Add(a, b);
    b[sign] = (b[sign] == '-' ? '+' : '-');
    return res;
}

int * HLMul (int * a, int b)
{
    tlong(res);
    SET(res, 0, 0, N - 1);
    res[sign] = a[sign];
    res[dot] = a[dot];
    res[base] = a[base];
    if (b < 0)
    {
        res[sign] = (a[sign] == '-' ? '+' : '-');
        b *= -1;
    }
    int p = 0;
    for (int i = 0; i < a[len] || p; i++)
    {
        res[i] = a[i] * b + p;
        p = res[i] / res[base];
        res[i] %= res[base];
    }
    res[len] = lenL(res);
    return res;
}

int HLDiv (int * a, int b, int smb)
{
    SetPrecision(a, smb);
    if (b < 0)
    {
        a[sign] = (a[sign] == '-' ? '+' : '-');
        b *= -1;
    }
    int p = 0;
    REPD(i, a[len])
    {
        p = p * a[base] + a[i];
        a[i] = p / b;
        p %= b;
    }
    a[len] = lenL(a);
    return p;
}

int * Multi (int * a, int * b)
{
    tlong(res);
    SET(res, 0, 0, N - 1);
    res[dot] = a[dot] + b[dot];
    res[base] = a[base];
    res[sign] = (a[sign] == b[sign] ? '+' : '-');
    REP(j, b[len])
    {
        int p = 0;
        for (int i = 0; i < a[len] || p; i++)
        {
            res[i + j] += a[i] * b[j] + p;
            p = res[i + j] / res[base];
            res[i + j] %= res[base];
        }
    }
    res[len] = lenL(res);
    return res;
}

int * Divide (int * a, int * b, int smb)
{
    SetPrecision(a, smb);
    tlong(res); tlong(ost);
    SET(res, 0, 0, N - 1);
    SET(ost, 0, -4, N - 1);

    res[sign] = (a[sign] == b[sign] ? '+' : '-');
    res[dot] = a[dot];
    res[base] = ost[base] = a[base];
    ost[sign] = '+';

    REPD(i, a[len])
    {
        shift(ost, 1);
        ost[dot] = 0;
        ost[0] = a[i];
        while (comp_abs(ost, b) >= 0)
        {
            res[i]++;
            ost = subL_abs(ost, b);
            SetPrecision(ost, 0);
        }
    }
    res[len] = lenL(res);
    return res;
}

ifstream f1("inp1.txt");
ifstream f2("inp2.txt");
ofstream f("output.txt");

tlong(A);
tlong(B);
tlong(C);

#define ONLINE_JUDGE
int main ()
{
    #ifndef ONLINE_JUDGE
        freopen ("input.txt", "r", stdin);
        freopen ("output.txt", "w", stdout);
    #endif
    A = inputL(f1); A[base] = 10;
    B = inputL(f1); B[base] = 10;
    f << comp_abs(A, B)<< endl;
    C = Divide(A, B, 4);
    outputL(C, f);
    return 0;
}
