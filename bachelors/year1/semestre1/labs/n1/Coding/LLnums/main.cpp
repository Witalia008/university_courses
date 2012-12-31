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

#define fstm fstream

const string TMP = "__tmp1.txt";
const string TMP1 = "__tmp2.txt";
const string TMP2 = "__tmp3.txt";
const string TMP3 = "__tmp4.txt";
const string TMP4 = "__tmp5.txt";
const string TMP5 = "__tmp6.txt";

char get_prev (fstm &f)
{
    if (!f.tellg()) return 0;
    f.seekg(f.tellg() - (streamsize)1);
    char res = f.get();
    f.seekg(f.tellg() - (streamsize)2);
    return res;
}

void reverse_file(string f1, string f2)
{
    fstm inp (f1.c_str(), fstm::in);
    fstm out (f2.c_str(), fstm::out);
    inp.seekg(0, ios::end);
    get_prev(inp);
    while (inp.tellg())
        out << get_prev(inp);
    out << endl;
    inp.close();
    out.close();
}

int get_pt (fstm &f)
{
    f.seekg(0, ios::end);
    get_prev(f);
    int ans = 0;
    bool fl = false;
    while (f.tellg())
    {
        char cur = get_prev(f);
        if (cur == '.') fl = true; else
        if (!fl) ans++;
    }
    if (!fl) ans = 0;
    return ans;
}

int length (fstm &f)
{
    f.seekg(0, ios::end);
    int res = f.tellg();
    if (get_pt(f)) res--;
    f.seekg(0, ios::beg);
    while (f.get() == '0') res--;
    f.seekg(0, ios::beg);
    return res - 2;
}

void copy_file(string a, string b)
{
    fstm f1 (a.c_str(), fstm::in);
    fstm f2 (b.c_str(), fstm::out);
    while (!f1.eof())
    {
        char q = -1;
        f1 >> q;
        if (q != -1) f2 << q;
    }
    f2 << endl;
    f1.close();
    f2.close();
}

void push_bk (string fn, char wh)
{
    copy_file (fn, TMP3);
    fstm ff (TMP3.c_str(), fstm::in);
    fstm fo (fn.c_str(), fstm::out);
    char q = -1;
    ff >> q;
    while (q != -1)
    {
        fo << q;
        q = -1;
        ff >> q;
    }
    fo << wh << endl;
    fo.close();
    ff.close();
}

int comp (fstm &f1, fstm &f2)
{
    int p1 = get_pt(f1), l1 = length(f1);
    int p2 = get_pt(f2), l2 = length(f2);
    if (l1 - p1 != l2 - p2)
        return l1 - p1 < l2 - p2 ? -1 : 1;
    f1.seekg(0, ios::beg);
    while (f1.get() == '0') ;
    get_prev(f1);get_prev(f1);
    f2.seekg(0, ios::beg);
    while (f2.get() == '0') ;
    get_prev(f2);get_prev(f2);
    char a, b;
    a = b = '0';
    while (!f1.eof() || !f2.eof())
    {
        a = b = '0';
        f1 >> a;
        if (a == '.') a = f1.get();
        f2 >> b;
        if (b == '.') b = f2.get();
        if (a != b) break;
    }

    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

int compF (string fn1, string fn2)
{
    fstm f1 (fn1.c_str(), fstm::in);
    fstm f2 (fn2.c_str(), fstm::in);
    int res = comp(f1, f2);
    f1.close(); f2.close();
    return res;
}

void SumLLL (string fn1, string fn2, string fo, string lo)
{
    fstm fi1 (fn1.c_str(), fstm::in);
    fstm fi2 (fn2.c_str(), fstm::in);
    fstm fo1 (TMP3.c_str(), fstm::out);
    fstm log (lo.c_str(), fstm::out);

    int p1, p2;
    p1 = get_pt (fi1);
    p2 = get_pt (fi2);
    fi1.seekg(0, ios::end);
    get_prev(fi1);
    fi2.seekg(0, ios::end);
    get_prev(fi2);
    int P = 0;
    if (p1 > p2)
    {
        REP(i, p1 - p2)
            fo1 << get_prev(fi1);
        P = p2;
    } else {
        REP(i, p2 - p1)
            fo1 << get_prev(fi2);
        P = p1;
    }

    int p = 0;
    int l = 0;
    while (fi1.tellg() || fi2.tellg())
    {
        if (!P && l) fo1 << '.';
        int a = '0', b = '0';
        if (fi1.tellg()) a = get_prev(fi1);
        if (a == '.') a = get_prev(fi1);
        if (fi2.tellg()) b = get_prev(fi2);
        if (b == '.') b = get_prev(fi2);
        if (a == '+' || a == '-') a = '0';
        if (b == '+' || b == '-') b = '0';
        a -= '0'; b -= '0';
        int res = p + a + b;
        fo1 << res % 10;
        p = res / 10;
        P--;
        l++;
    }
    fo1 << endl;

    fi1.close();
    fi2.close();
    fo1.close();
    log.close();
    reverse_file(TMP3, fo);
}

void SubLLL (string fn1, string fn2, string fo, string lo)
{
    fstm fi1 (fn1.c_str(), fstm::in);
    fstm fi2 (fn2.c_str(), fstm::in);
    fstm fo1 (TMP3.c_str(), fstm::out);
    fstm log (lo.c_str(), fstm::out);

    int p1, p2;
    p1 = get_pt (fi1);
    p2 = get_pt (fi2);
    fi1.seekg(0, ios::end);
    get_prev(fi1);
    fi2.seekg(0, ios::end);
    get_prev(fi2);
    int P = 0;

    int z = 0;
    if (p1 > p2)
    {
        REP(i, p1 - p2)
            fo1 << get_prev(fi1);
        P = p2;
    } else {
        REP(i, p2 - p1)
        {
            char q = get_prev(fi2);
            if (q != '0' || z)
            {
                fo1 << '0' + 10 - z - q;
                z = 1;
            }
        }
        P = p1;
    }

    int l = 0;
    while (fi1.tellg() || fi2.tellg())
    {
        if (!P && l) fo1 << '.';
        int a = '0', b = '0';
        if (fi1.tellg()) a = get_prev(fi1);
        if (a == '.') a = get_prev(fi1);
        if (fi2.tellg()) b = get_prev(fi2);
        if (b == '.') b = get_prev(fi2);
        if (a == '+' || a == '-') a = '0';
        if (b == '+' || b == '-') b = '0';
        a -= '0', b -= '0';
        int res = a - b - z;
        z = res < 0;
        if (z) res += 10;
        fo1 << res;
        P--;
        l++;
    }
    fo1 << endl;

    fi1.close();
    fi2.close();
    fo1.close();
    log.close();
    reverse_file(TMP3, fo);
}

void MultiLLL(string fn1, string fn2, string fo, string lo)
{
    fstm fi1 (fn1.c_str(), fstm::in);
    fstm fi2 (fn2.c_str(), fstm::in);
    fstm log (lo.c_str(), fstm::out);
    fstm fo1, fo2;// (TMP.c_str(), fstm::out);

    int p1 = get_pt(fi1);
    int p2 = get_pt(fi2);
    int P = p1 + p2;

    fi2.seekg(0, ios::end);
    get_prev(fi2);

    fo1.open(TMP.c_str(), fstm::out);
    fo1<<0<<endl;
    fo1.close();
    int cnt = 0;
    while (fi2.tellg())
    {
        int a = get_prev(fi2);
        if (a == '.') a = get_prev(fi2);
        a -= '0';
        fi1.seekg(0, ios::end);
        get_prev(fi1);
        int p = 0;
        fo2.open(TMP1.c_str(), fstm::out);
        REP(i, cnt) fo2<<0;
        cnt++;
        while (fi1.tellg() || p)
        {
            int b = 0;
            if (fi1.tellg()) b = get_prev(fi1) - '0';
            if (b == '.' - '0') b = get_prev(fi1) - '0';
            int res = a * b + p;
            p = res / 10;
            fo2 << res % 10;
        }
        fo2<<endl;
        fo2.close();
        reverse_file(TMP1, TMP2);
        copy_file(TMP, TMP1);
        SumLLL(TMP1, TMP2, TMP, "log1.txt");
    }

    fi1.close();
    fi2.close();
    log.close();
    fo1.open(TMP.c_str(), fstm::in);
    fo2.open(fo.c_str(), fstm::out);

    int len = length(fo1);
    while (!fo1.eof())
    {
        char q = -1;
        fo1 >> q;
        if (len == P && P) fo2 << '.';
        if (q != -1) fo2 << q;
        len--;
    }
    fo1.close();
    fo2.close();
}

void DivideLLL(string fn1, string fn2, string fres, string fost, string lo)
{
    fstm fi1 (fn1.c_str(), fstm::in);
    fstm fi2 (fn2.c_str(), fstm::in);

    int p1 = get_pt(fi1);
    int p2 = get_pt(fi2);
    int P = max (p1, p2);

    fstm fnn (TMP4.c_str(), fstm::out);
    fnn << 1;
    REP(i, P) fnn << 0;
    fnn << endl;
    fnn.close();

    fi1.close();
    fi2.close();
    MultiLLL(fn1, TMP4, TMP5, "log1.txt");
    copy_file (TMP5, fn1);
    MultiLLL(fn2, TMP4, TMP5, "log1.txt");
    copy_file (TMP5, fn2);

    fi1.open (fn1.c_str(), fstm::in);
    fstm fo1 (fres.c_str(), fstm::out);
    fstm log (lo.c_str(), fstm::out);

    fi2.open (TMP.c_str(), fstm::out);
    fi2.close();

    bool fl = false;
    while (!fi1.eof())
    {
        char a = -1;
        fi1 >> a;
        if (a == -1 || a == '.') break;
        push_bk (TMP, a);
        int res = 0;
        while (compF (TMP, fn2) >= 0)
        {
            SubLLL(TMP, fn2, TMP1, "log1.txt");
            copy_file(TMP1, TMP);
            res++;
        }
        if (res || fl) fo1 << res;
        fl = fl || (res != 0);
    }
    fo1<<endl;

    copy_file(TMP, fost);
    fo1.close();
    fi2.close();
    log.close();
}

int main()
{
    //SubLLL("inp1.txt", "inp2.txt", "out.txt", "log.txt");
    DivideLLL("inp1.txt", "inp2.txt", "out.txt", "ost.txt", "log.txt");
    //SubLLL("inp1.txt", "inp2.txt", "out.txt", "log.txt");
    //reverse_file("inp1.txt", "out.txt");
    /*fstm f1 ("inp1.txt", fstm::app);
    fstm f2 ("inp2.txt", fstm::in);
    f1.close(); f2.close();*/
    return 0;
}
