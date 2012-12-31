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
#include "longnums.cpp"
#include "verylong.cpp"

using namespace std;

#define For(i,a,b,d) for (int i = (a); i != (b); i += d)
#define FORD(i,a,b) for (int i = (a); i >= b; i--)
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define REPD(i,n) for (int i = (n - 1); i >= 0; i--)
#define REP(i,n) for (int i = 0; i < (n); i++)
#define CLR(a,x) memset(a,x,sizeof(a))
#define pb push_back
#define mp make_pair
#define eps 10e-7
#define InfL 10000000000000000LL
#define Inf 2000010000
#define Mi 100000000
#define N 1000015
#define K 105
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
inline ll gcd (ll a, ll b) { return (!b ? a : gcd (b, a % b)); }
inline ll minn (ll a, ll b) { return a < b ? a : b; }
inline ll maxx (ll a, ll b) { return a > b ? a : b; }

void outfile (string s)
{
    ifstream f(s.c_str());
    while (!f.eof())
    {
        string s;
        getline(f, s);
        cout << s << endl;
    }
    f.close();
}

void writeInFile (string s, string fname)
{
    ofstream f(fname.c_str());
    f << s << endl;
    f.close();
}

string s, a, b, c, d;
TLong A, B, C;
int k;

int main()
{
    outfile("greetings.txt");
    for (cin >> s; s != "exit"; cin >> s)
    {
        if (s == "man")
            outfile("greetings.txt");
        else if (s == "write")
        {
            cin >> a >> b;
            writeInFile(a, b);
        } else if (s == "show")
        {
            cin >> a;
            outfile(a);
        } else if (s == "getlen")
        {
            cin >> a;
            A.Input(a, 10);
            cout << "Length of number is" << A.len << endl;
        } else if (s == "comp")
        {
            cin >> a >> b >> c;
            A.Input(a, 10);
            B.Input(b, 10);
            ofstream fout(c.c_str());
            switch (A.Comp(B))
            {
                case -1: fout << "A is bigger than B" << endl; break;
                case 1: fout << "A is lower than B" << endl; break;
                case 0: fout << "A is equal to B" << endl; break;
            }
            fout.close();
        } else if (s == "+" || s == "-" || s == "*" || s == "/" || s == "gcd" || s == "^")
        {
            cin >> a >> b >> c;
            A.Input(a, 10);
            B.Input(b, 10);
            if (s == "+") C = A + B;
            if (s == "-") C = A - B;
            if (s == "*") C = A * B;
            if (s == "/") C = A / B;
            if (s == "gcd") A.GCD(A, B), C = A;
            if (s == "^") C = A.Power(A, B, 10);
            C.Output(c);
        } else if (s == "sqrt")
        {
            cin >> a >> c >> k;
            A.Input(a, 10);
            C = A.Root(A, k);
            C.Output(c);
        } else if (s == "++")
        {
            char p1, p2;
            cin >> p1 >> a >> p2 >> b >> c;
            HolySum(a, p1, b, p2, c);
        } else if (s == "--")
        {
            char p1, p2;
            cin >> p1 >> a >> p2 >> b >> c;
            p2 = (p2 == '-' ? '+' : '-');
            HolySum(a, p1, b, p2, c);
        } else if (s == "**")
        {
            char p1, p2, q;
            cin >> p1 >> a >> p2 >> b >> c;
            MultiLLL(a, b, c, "log.txt");
            q = (p1 == p2 ? '+' : '-');
            SetSign (c, q);
        } else if (s == "//")
        {
            char p1, p2, q;
            cin >> p1 >> a >> p2 >> b >> c >> d;
            DivideLLL(a, b, c, d, "log.txt");
            q = (p1 == p2 ? '+' : '-');
            SetSign (c, q);
        } else if (s == "COMP")
        {
            cin >> a >> b >> c;
            ofstream fout(c.c_str());
            switch (compF(a, b))
            {
                case -1: fout << "A is bigger than B" << endl; break;
                case 1: fout << "A is lower than B" << endl; break;
                case 0: fout << "A is equal to B" << endl; break;
            }
            fout.close();
        } else if (s == "POW")
        {
            cin >> a >> b >> c;
            PowerLLL(a, b, c, "log.txt");
        } else if (s == "log"){
            cin >> a;
            ifstream dd (a.c_str(), fstream::in);
            while (!dd.eof())
            {
                getline(dd, b);
                cout << dd << endl;
            }
            dd.close();
        }
    }
    return 0;
}
