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

string toStr(int a)
{
    string res = "";
    while (a)
    {
        res += a % 10 + '0';
        a /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

vector<string> hist;
string s, A, a, b;
ld n;
int k;

int bss = 2;
#define ONLINE_JUDGE
int main ()
{
    #ifndef ONLINE_JUDGE
        freopen ("input.txt", "r", stdin);
        freopen ("output.txt", "w", stdout);
    #endif
    cout << "w1 - enter first number" << endl;
    cout << "w2 - enter second number" << endl;
    cout << "setbs - set base of numbers" << endl;
    cout << "do ch - do operation ch" << endl;
    cout << "show id- to show result of action number id. id id==-1 - show all" << endl;
    cout << "exit - terminate program" << endl;
    cout << "man - manual for programme" << endl;
    for (cin >> s; s != "exit"; cin >> s)
    {
        if (s == "setbs")
        {
            cin >> bss;
            cout << "succesfully" << endl;
        } else
        if (s == "man")
        {
            cout << "This program does operations with two numbers in some system" << endl;
            cout << "operations are >=, +, -, *, /" << endl;
        }else
        if (s == "w1" || s == "w2")
        {
            ofstream fout (s == "w1" ? "inp1.txt" : "inp2.txt");
            cin >> s;
            bool fl = true;
            REP(i, s.length())
            {
                int cur = -1;
                if (s[i] >= 'A' && s[i] <= 'Z') cur = s[i] - 'A' + 36; else
                if (s[i] >= 'a' && s[i] <= 'z') cur = s[i] - 'a' + 10; else
                if (s[i] >= '0' && s[i] <= '9') cur = s[i] - '0';
                if ((cur < 0 || cur >= bss) && s[i] != '.' && s[i] != '-')
                {
                    cout << "Wrong number" << endl;
                    fl = false;
                    break;
                }
            }
            if (fl) fout << s << endl;
            fout.close();
            if (fl) cout << "successfully" << endl;
        } else
        if (s == "show")
        {
            cin >> k;
            if (k == -1)
                REP(i, hist.size())
                    cout << hist[i] << endl;
            else{
                if (k >= 0 && k < hist.size())
                    cout << hist[k] << endl;
                else
                    cout << "there were not operation with this number";
            }
        } else
        if (s == "do")
        {
            char ch;
            cin >> ch;
            ifstream fin;
            fin.open("inp1.txt");
            fin >> a;
            fin.close();
            fin.open("inp2.txt");
            fin >> b;
            fin.close();
            ofstream fout ("out1.txt");
            ld nA = toDec(a, bss);
            ld nB = toDec(b, bss);
            s = "[" + toStr(bss) + "]";
            if (ch == '>')
            {
                s += a + ch + b;
                if (nA < nB) s += "== false"; else s += "== true";
                hist.pb(s);
            } else
            if (ch == '+')
            {
                s += a + ch + b + "==" + fromDec(nA + nB, bss);
                hist.pb(s);
            } else
            if (ch == '-')
            {
                s += a + ch + b + "==" + fromDec(nA - nB, bss);
                hist.pb(s);
            } else
            if (ch == '*')
            {
                s += a + ch + b  + "==" + fromDec(nA * nB, bss);
                hist.pb(s);
            } else
            if (ch == '/')
            {
                if (!nB)
                {
                    cout << "division by zero" << endl;
                    continue;
                }
                s += a + ch + b  + "==" + fromDec(nA / nB, bss);
                hist.pb(s);
            } else
            {
                cout << "no such operation" << endl;
                continue;
            }
            REP(i, hist.size())
                fout << hist[i] << endl;
            fout.close();
            cout << "done" << endl;
        } else {
            cout << "fault" << endl;
        }
    }
    return 0;
}
