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
#define eps 10e-3
#define Inf 1000000000
#define Mi 1000000007
#define N 100015
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
inline ll gcd (ll a, ll b){ return (!b ? a : gcd (b, a % b)); }

int cyfr (char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    if (c >= 'A' && c <= 'Z') return c - 'A' + 36;
    return -1;
}

char chr (int c)
{
    if (c >= 0 && c < 10) return c + '0';
    if (c >= 10 && c < 36) return c - 10 + 'a';
    if (c >= 36 && c < 52) return c - 36 + 'A';
    return -1;
}

ld toDec(string a, int &base)
{
    int sign = 1;
    if (a[0] == '-')
    {
        a.erase(0, 1);
        sign = -1;
    }
    int pos = a.length();
    REP(i, a.length())
    {
        base = max (base, cyfr(a[i]) + 1);
        if (a[i] == '.')
            pos = i;
    }
    ld r1 = 0, r2 = 0;
    REP(i, pos)
        r1 = r1 * base + cyfr(a[i]);
    a[pos] = '0';
    for (int i = a.length() - 1; i >= pos; i--)
        r2 = r2 / base + cyfr(a[i]);
    return (r1 + r2) * sign;
}

string fromDec(ld n, int base)
{
    if (base < 2 || base > 52) return "wrong base";
    string sign = "";
    if (n < 0) n = -n, sign = "-";
    string r1="", r2="";
    for (ll i = ll(n); i; i /= base)
        r1 += chr(i % base);
    n -= ll(n);
    for (int i = 0; i < 1000 && n; i++)
    {
        r2 += chr (int (n * base));
        n *= base;
        n -= int(n);
    }
    if (r1 == "") r1 = "0";
    reverse (r1.begin(), r1.end());
    r1 = sign + r1;
    if (r2 != "") r1 += "." + r2;
    return r1;
}

string s, A;
int k;

#define ONLINE_JUDGE
int main ()
{
    #ifndef ONLINE_JUDGE
        freopen ("input.txt", "r", stdin);
        freopen ("output.txt", "w", stdout);
    #endif
    cout << "w1 - enter number" << endl;
    cout << "w2 - enter base" << endl;
    cout << "do - translate number" << endl;
    cout << "show - to show result" << endl;
    cout << "exit - terminate program" << endl;
    cout << "man - manual for programme" << endl;
    for (cin >> s; s != "exit"; cin >> s)
    {
        if (s == "man")
        {
            cout << "This program translates one number from some system to dec." << endl;
            cout << "Cyfrs are 1, 2, .. , 9, a, b, .. , z, A, B, .. , Z" << endl;
        }else
        if (s == "w1")
        {
            ofstream fout ("inp1.txt");
            cin >> s;
            bool fl = true;
            REP(i, s.length())
                if (cyfr(s[i]) == -1 && s[i] != '.' && s[i] != '-')
                    fl = false;
            if (fl) fout << s << endl;
            else cout << "wrong format of number" << endl;
            fout.close();
            if (fl) cout << "succesully" << endl;
        } else
        if (s == "w2")
        {
            ofstream fout ("inp2.txt");
            cin >> k;
            fout << k << endl;
            fout.close();
            cout << "succesully" << endl;
        } else
        if (s == "show")
        {
            ifstream fin("out1.txt");
            getline(fin, s);
            cout << s << endl;
            fin.close();
        } else
        if (s == "do")
        {
            ifstream fin;
            fin.open("inp1.txt");
            fin >> A;
            fin.close();
            fin.open("inp2.txt");
            fin >> k;
            fin.close();
            ofstream fout ("out1.txt");
            fout << A << "[" << k << "]" << " = " << toDec(A, k) << "[10]\n";
            fout.close();
            cout << "done" << endl;
        } else {
            cout << "fault" << endl;
        }
    }
    return 0;
}
