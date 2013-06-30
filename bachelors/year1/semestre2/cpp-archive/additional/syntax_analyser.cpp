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
//#include <assert.h>

using namespace std;

#define For(i,a,b,d) for (int i = (a); i != (b); i += d)
#define FORD(i,a,b) for (int i = (a); i >= b; i--)
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define REPD(i,n) for (int i = (n - 1); i >= 0; i--)
#define REP(i,n) for (int i = 0; i < (n); i++)
#define ALL(a) (a).begin(), (a).end()
#define CLR(a,x) memset(a,x,sizeof(a))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define Abs(a) ((a < 0) ? -(a) : a)
#define sqr(a) ((a)*(a))
#define pb push_back
#define mp make_pair
#define eps 10e-5
#define Inf 1000000000
#define Mi 1000000007
#define N 200005
#define K 32

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

inline ll gcd (ll a, ll b){ return (!b ? a : gcd (b, a % b)); }

const ld PI = 2 * acos(0.0);
const ll InfLL = ll(Inf) * ll(Inf);

int rand15() { return rand() % (1 << 15); }
int rand30() { return (rand15() << 15) + rand15(); }
int rand(int L, int R) { if (L > R) return R; return rand30() % (R - L + 1) + L; }
ld random(ld L, ld R) { return rand(ceil((L-eps)*100), floor((R+eps)*100)) / 100.0;}

//#define DEBUG

string s;

void do_op (double &a, double b, char op) {
    if (op == '-' || op == '+') {
        a += b * (op == '+' ? 1 : -1);
    } else if (op == '*') {
        a *= b;
    } else if (op == '/') {
        a /= b;
    } else if (op == '^') {
        a = pow(a, b);
    }
}

double do_func (double a, string func) {
    if (func == "sin") {
        return sin(a);
    } else if (func == "cos") {
        return cos(a);
    } else if (func == "tg") {
        return tan(a);
    } else if (func == "ctg") {
        return 1 / tan(a);
    }
}

int cur;

const int cnt_opers = 3;
const int cnt_funcs = 4;

string operators[cnt_opers] = {"+-", "*/", "^"};
string functions[cnt_funcs] = {"sin", "cos", "tg", "ctg"};

double expression(int);
double function(int);
double read_number();
double operand();

double expression (int op_num) {
    if (op_num == cnt_opers) {
        return function(0);
    }
    double res = expression(op_num + 1);
    while (cur < s.length() && operators[op_num].find(s[cur]) != -1) {
        char cur_op = s[cur++];
        do_op(res, expression(op_num + 1), cur_op);
    }
    return res;
}

double function (int func_num) {
    if (func_num == cnt_funcs) {
        return operand();
    }
    if (functions[func_num] == s.substr(cur, functions[func_num].length())) {
        return (cur += functions[func_num].length(), do_func(operand(), functions[func_num]));
    } else {
        return function(func_num + 1);
    }
}

double operand () {
    if (s[cur] >= '0' && s[cur] <= '9') {
        return read_number();
    } else {
        double res = (cur++, expression(0));
        return (cur++, res);
    }
}

double read_number() {
    double r1 = 0, r2 = 0;
    while (cur < s.length() && s[cur] >= '0' && s[cur] <= '9') {
        r1 = r1 * 10 + s[cur++] - '0';
    }
    if (cur < s.length() && s[cur] == '.') {
        cur++;
        int j = cur;
        while (j < s.length() && s[j] >= '0' && s[j] <= '9') {
            j++;
        }
        while (j > cur) {
            r2 = (r2 + s[--j] - '0') / 10;
        }
        while (cur < s.length() && s[cur] >= '0' && s[cur] <= '9') {
            cur++;
        }
    }
    return r1 + r2;
}


//#define DEBUG_MODE
//#define ONLINE_JUDGE
int main ()
{
    std::ios_base::sync_with_stdio(0);
    #ifndef ONLINE_JUDGE
        freopen ("input.txt", "r", stdin);
        freopen ("output.txt", "wb", stdout);
    #endif
    cin >> s;
    cout << expression(0) << endl;
    return 0;
}