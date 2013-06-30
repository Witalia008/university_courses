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

#define For(i, a, b, d) for (int i = (a); i != (b); i += d)
#define FORD(i, a, b) for (int i = (a); i >= b; i--)
#define FOR(i, a, b) for (int i = (a); i <= (b); i++)
#define REPD(i, n) for (int i = (n - 1); i >= 0; i--)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define CLR(a, x) memset(a, x, sizeof(a))
#define pb push_back
#define mp make_pair
#define eps 10e-3
#define Inf 1000000000
#define Mi 1000000007
#define N 1000015
#define K 15

typedef double ld;
typedef long long ll;
typedef int i;
typedef vector<i> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef pair<double, char> pdc;
typedef enum
{
    heavy,
    light
} lbl;

const int mx[4] = {1, -1, 0, 0};
const int my[4] = {0, 0, 1, -1};

inline ll Abs(ll x) { return x < 0 ? -x : x; }
inline ll sqr(ll a) { return a * a; }
inline ll gcd(ll a, ll b) { return (!b ? a : gcd(b, a % b)); }

//#define DEBUG_MODE

bool is_chr(char a)
{
    return a >= '0' && a <= '9' || a >= 'a' && a <= 'z';
}

bool is_op(char a)
{
    return a == '-' || a == '+' || a == '/' || a == '*';
}

char rev(char a)
{
    return (a == ')' ? '(' : (a == ']' ? '[' : '{'));
}

bool do_op(vector<char> &st, vector<char> &op)
{
    if (st.size() < 2)
        return false;
    if (!op.size())
        return false;
    if (!is_op(op.back()))
        return false;
    st.pop_back();
    op.pop_back();
    return true;
}

bool op_br(char a)
{
    return a == '(' || a == '[' || a == '{';
}

bool cl_br(char a)
{
    return a == ')' || a == ']' || a == '}';
}

bool check(string s)
{
    vector<char> op, st;
    op.clear();
    st.clear();
    REP(i, s.length())
    if (i && (s[i] == '-' || s[i] == '+') && s[i - 1] == '(')
        s.insert(i, "0");
    REP(i, s.length())
    {
        if (i && op_br(s[i]) && !is_op(s[i - 1]))
            s.insert(i, "*");
        if (i && !is_op(s[i]) && cl_br(s[i - 1]))
            s.insert(i, "*");
    }
    REP(i, s.length())
    {
        if (is_chr(s[i]))
        {
            while (i < s.length() && is_chr(s[i]))
                ++i;
            --i;
            st.push_back('0');
        }
        else if (op_br(s[i]))
            op.push_back(s[i]);
        else if (cl_br(s[i]))
        {
            while (op.size() && op.back() != rev(s[i]))
                if (!do_op(st, op))
                    return false;
            if (!op.size())
                return false;
            op.pop_back();
        }
        else if (is_op(s[i]))
        {
            op.push_back(s[i]);
        }
        else
            return false;
    }
    while (op.size())
        if (!do_op(st, op))
            return false;
    if (st.size() != 1)
        return false;
    return true;
}

bool is_correct(string a)
{
    string s = "";
    bool fl = true;
    REP(i, a.length())
    {
        if (a[i] == '<' || a[i] == '>' || a[i] == '=')
        {
            fl = fl && check(s);
            s = "";
        }
        else
            s += a[i];
    }
    fl = fl && check(s);
    return fl;
}

//#define ONLINE_JUDGE
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    string s;
    cin >> s;
    cout << (is_correct(s) ? "GOOD" : "NOT GOOD") << endl;
    return 0;
}
