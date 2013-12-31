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

bool isWhitespace(char q) {
    return q == ' ';
}

bool isUnary(char q) {
    return q == '-' || q == '+';
}

bool isOper(char q) {
    if (q < 0) q = -q;
    return string("-+/*").find(q) != -1;
}

int prior(char q) {
    if (q < 0)
        return 4;
    return q == '-' || q == '+' ? 1 : 
        q == '/' || q == '*' || q == '%' ? 2 :
        -1;
}

string getPost(const string& s) {
    stack<char> ops;
    string res = "";
    bool canUnary = true;
    for (int i = 0; i < s.size(); ++i) {
        if (!isWhitespace(s[i])) {
            if (s[i] == '(') {
                canUnary = true;
                ops.push('(');
            } else if (s[i] == ')') {
                canUnary = false;
                while (ops.top() != '(') {
                    res += ops.top();
                    ops.pop();
                }
                ops.pop();
            } else if (isOper(s[i])) {
                char curop = s[i];
                if (canUnary && isUnary(curop))
                    curop = -curop;
                while (ops.size() && prior(ops.top()) >= prior(curop) + (curop < 0)) {
                    res += ops.top();
                    ops.pop();
                }
                ops.push(curop);
                canUnary = true;
            } else if (isdigit(s[i])) {
                while (i < s.size() && isdigit(s[i]))
                    res += s[i++];
                res += " ";
                --i;
                canUnary = false;
            }
        }
    }
    while (ops.size()) {
        res += ops.top();
        ops.pop();
    }
    return res;
}

void doOp(stack<double> & st, char op) {
    double a, b;
    if (op < 0) {
        a = st.top(); st.pop();
        st.push(-a);
    } else {
        b = st.top(); st.pop();
        a = st.top(); st.pop();
        if (op == '+')
            st.push(a + b);
        else if (op == '-')
            st.push(a - b);
        else if (op == '*')
            st.push(a * b);
        else if (op == '/') {
            if (b == 0)
                throw runtime_error("division by zero");
            st.push(a / b);
        }
    }
}

double execute(string s) {
    stack<double> st;
    for (int i = 0; i < s.size(); ++i) {
        if (isOper(s[i])) {
            doOp(st, s[i]);
        } else if (isdigit(s[i])) {
            int cur = 0;
            while (i < s.size() && isdigit(s[i]))
                cur = cur * 10 + s[i++] - '0';
            --i;
            st.push(cur);
        }
    }
    return st.top();
}

//#define ONLINE_JUDGE
int main () {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    string expr;
    cin >> expr;
    string post = getPost(expr);
    cout << execute(post) << endl;
    return 0;
}