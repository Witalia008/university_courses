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
#define N 1000005
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
inline ll sqr (ll a) { return a*a; }
inline ll gcd (ll a, ll b) { return (!b ? a : gcd (b, a % b)); }
inline ll minn (ll a, ll b) { return a < b ? a : b; }
inline ll maxx (ll a, ll b) { return a > b ? a : b; }


struct dish
{
    string name;
    vector<string> descr;
    double price;
    int prior;
    int cnt;
    void getDish ()
    {
        cout << "Enter name of dish\n";
        cin >> name;
        cout << "Enter description. '---' - end of descr.\n";
        while (name.length() > 100) name.erase(name.length()-1, 1);
        string s;
        cin >> s;
        while (s != "---")
            descr.pb(s), cin >> s;
        cout << "Enter price\n";
        cin >> price;
        prior = cnt = 0;
    }
};

bool comp (dish a, dish b)
{
    return a.prior > b.prior || a.prior == b.prior && a.price > b.price;
}

struct TMenu
{
    string tDishs;
    vector<dish> A;
};

vector<TMenu> all;
dish a;
int curc;
string s;
int page;
string user;
fstream M;
fstream B;
const int pages = 1;
vector<pair<vector<pair<int, int> >, double> > prop;

void outPage ()
{
    FOR(i, page * pages, min(page * pages + pages, int(all[curc].A.size())) - 1)
        cout << i - page << ". " << all[curc].A[i].name << " " << all[curc].A[i].price << endl;
}

void outSmthng ()
{
    fstream t ("greet.txt", fstream::in);
    string s = "";
    while (!t.eof())
    {
        getline(t, s);
        cout << s << endl;
    }
    t.close();
}

void getAllProp (string tt)
{
    REP(i, prop.size())
    {
        int fl = -1;
        REP(j, prop[i].first.size())
            if (all[prop[i].first[j].first].A[prop[i].first[j].second].name == tt)
                fl = j;
        if (tt == "-") fl = prop[i].first.size();
        if (fl != -1)
        {
            cout << "If you also buy:\n";
            REP(j, prop[i].first.size())
                if (j != fl && !all[prop[i].first[j].first].A[prop[i].first[j].second].cnt)
                    cout << all[prop[i].first[j].first].tDishs << " " << all[prop[i].first[j].first].A[prop[i].first[j].second].name << " " << all[prop[i].first[j].first].A[prop[i].first[j].second].price << endl;
            cout << "You will have " << prop[i].second * 100 << " percent discount\n";
        }
    }
}

#define ONLINE_JUDGE
int main ()
{
    #ifndef ONLINE_JUDGE
        freopen ("input.txt", "r", stdin);
        freopen ("output.txt", "w", stdout);
    #endif
    M.open("menu.txt", fstream::in);
    int n;
    M >> n;
    all.resize(n);
    string xxx;
    REP(i, n)
    {
        M >> all[i].tDishs;
        int m;
        M >> m;
        getline(M, xxx);
        all[i].A.resize(m);
        REP(j, m)
        {
            getline(M, all[i].A[j].name);
            getline(M, s);
            while (s != "---")
            {
                all[i].A[j].descr.pb(s);
                getline (M, s);
            }
            M >> all[i].A[j].price;
            M >> all[i].A[j].prior;
            all[i].A[j].cnt = 0;
            getline(M, xxx);
        }
    }
    M.close();
    M.open("comb.txt", fstream::in);
    M >> n;
    prop.resize(n);
    REP(i, prop.size())
    {
        int m;
        M >> m;
        prop[i].first.resize(m);
        M >> prop[i].second;
        REP(j, prop[i].first.size())
            M >> prop[i].first[j].first >> prop[i].first[j].second;
    }
    M.close();
    cout << "Welcome!\n";
    outSmthng();
    for (cin >> s; s != "exit"; cin >> s)
    {
        if (s == "login")
        {
            cout << "Enter your login\n";
            cin >> user;
            REP(i, all.size())
            {
                REP(j, all[i].A.size())
                    all[i].A[j].cnt = 0;
            }
        } else {
            if (s == "showt")
            {
                cout << "All categories are:\n";
                REP(i, all.size())
                    cout << all[i].tDishs << endl;
            } else
            if (s == "showd")
            {
                int wh = 0;
                string tt;
                cout << "Enter name of category you would like to look for.\n";
                cin >> tt;
                while (wh < all.size() && all[wh].tDishs != tt) ++wh;
                if (wh == all.size())
                    cout << "No such category\n";
                else {
                    cout << "All dishes in category " << all[wh].tDishs << " are:\n";
                    REP(j, all[wh].A.size())
                        cout << all[wh].A[j].name << endl;
                }
            } else
            if (s == "shownew")
            {
                REP(i, all.size())
                {
                    cout << all[i].tDishs << endl;
                    REP(j, min(10, int(all[i].A.size())))
                        cout << j << ". " << all[i].A[all[i].A.size()-1-j].name << " " << all[i].A[all[i].A.size()-1-j].price << endl;
                }
            } else
            if (s == "thebest")
            {
                REP(i, all.size())
                {
                    cout << all[i].tDishs << endl;
                    REP(j, min(3, int(all[i].A.size())))
                        cout << j << ". " << all[i].A[all[i].A.size()-1-j].name << " " << all[i].A[all[i].A.size()-1-j].price<< endl;
                }
            } else
            if (s == "opencat")
            {
                cout << "Enter name of category.\n";
                cin >> s;
                REP(i, all.size())
                    if (all[i].tDishs == s)
                        curc = i;
                page = 0;
                outPage();
            } else
            if (s == "nextp")
            {
                if ((page + 1) * 10 > all[curc].A.size()) ++page;
                outPage();
            } else
            if (s == "prevp")
            {
                if (page) page--;
                outPage();
            } else
            if (s == "book")
            {
                int k, cc;
                cout << "Enter number of dish in current page and how much you would like.\n";
                cin >> k >> cc;
                if (page * pages + k < all[curc].A.size())
                {
                    string tt = all[curc].A[page * pages + k].name;
                    getAllProp(tt);
                    all[curc].A[page * pages + k].cnt = max(0, all[curc].A[page * pages + k].cnt + cc);
                }
            } else
            if (s == "books")
            {
                string tt;
                int cc;
                cout << "Enter name of dish and how much you would like.\n";
                cin >> tt >> cc;
                REP(i, all[curc].A.size())
                    if (all[curc].A[i].name == tt)
                        all[curc].A[i].cnt = max (0, all[curc].A[i].cnt + cc);
                getAllProp (tt);
            } else
            if (s == "showprop")
            {
                string tt;
                cout << "Enter name of dish you would like to watch propositions with or '-' if doesn't matter\n";
                cin >> tt;
                getAllProp (tt);
            } else
            if (s == "showdescr")
            {
                int k;
                cout << "Enter number of dish in current page.\n";
                cin >> k;
                if (page * pages + k < all[curc].A.size())
                {
                    REP(i, all[curc].A[page * pages + k].descr.size())
                        cout << all[curc].A[page * pages + k].descr[i] << endl;
                }
            } else
            if (s == "endb")
            {
                double allsum = 0;
                int cn = 0;
                string tt;
                cout << "Enter name of file where your booking sould be saved.\n";
                cin >> tt;
                B.open(tt.c_str(), fstream::out);
                REP(i, prop.size())
                {
                    int howMany = Inf;
                    REP(j, prop[i].first.size())
                        howMany = min (howMany, all[prop[i].first[j].first].A[prop[i].first[j].second].cnt);
                    if (howMany)
                    {
                        B << "Combination (" << howMany << " times):\n";
                        double csum = 0;
                        REP(j, prop[i].first.size())
                        {
                            all[prop[i].first[j].first].A[prop[i].first[j].second].cnt--;
                            csum += all[prop[i].first[j].first].A[prop[i].first[j].second].price;
                            B << all[prop[i].first[j].first].A[prop[i].first[j].second].name << " " << all[prop[i].first[j].first].A[prop[i].first[j].second].price << endl;
                        }
                        B << "Price of comb: " << csum << "-" << (prop[i].second * 100) << "% = ";
                        csum *= (1 - prop[i].second);
                        B << csum << endl;
                        allsum += csum * howMany;
                    }
                }
                REP(i, all.size())
                    REP(j, all[i].A.size())
                        if (all[i].A[j].cnt)
                        {
                            cn++;
                            B << cn << ". " << all[i].tDishs << " " << all[i].A[j].name;
                            B << " " << all[i].A[j].price  << "*" << all[i].A[j].cnt << " = " << all[i].A[j].price * all[i].A[j].cnt << endl;
                            all[i].A[j].prior += all[i].A[j].cnt;
                            allsum += all[i].A[j].price * all[i].A[j].cnt;
                            all[i].A[j].cnt = 0;
                        }
                B << "Totally: " << allsum << endl;
                B.close();
            } else
            if (user == "root")
            {
                if (s == "dishadd")
                {
                    int wh = 0;
                    string tt;
                    cout << "Enter name of category.\n";
                    cin >> tt;
                    while (wh < all.size() && all[wh].tDishs != tt) ++wh;
                    if (wh == all.size())
                        cout << "No such category\n";
                    else {
                        a.getDish();
                        all[wh].A.pb(a);
                        cout << "Succesfully added.\n";
                    }
                } else
                if (s == "catadd")
                {
                    string tt;
                    cout << "Enter name of category\n";
                    cin >> tt;
                    all.resize(all.size() + 1);
                    all[all.size()-1].tDishs = tt;
                    cout << "Succesfully added.\n";
                } else
                if (s == "addcomb")
                {
                    prop.resize(prop.size() + 1);
                    REP(i, all.size())
                    {
                        cout << "Dish from category: " << all[i].tDishs << endl;
                        REP(j, all[i].A.size())
                            cout << j << ". " << all[i].A[j].name << endl;
                        int k;
                        cout << "Enter number of dish you would like to add. (-1 if no one)\n";
                        cin >> k;
                        if (k != -1)
                            prop[prop.size() - 1].first.pb(mp(i, k));
                        cout << "Enter discount for this combination\n";
                        cin >> prop[prop.size() - 1].second;
                    }
                }
            }
        }
        REP(i, all.size())
            sort (all[i].A.begin(), all[i].A.end(), &comp);
    }
    M.open("menu.txt", fstream::out);
    M << all.size() << endl;
    REP(i, all.size())
    {
        M << all[i].tDishs << endl;
        M << all[i].A.size() << endl;
        REP(j, all[i].A.size())
        {
            M << all[i].A[j].name << endl;
            REP(k, all[i].A[j].descr.size())
                M << all[i].A[j].descr[k] << endl;
            M << "---" << endl;
            M << all[i].A[j].price << endl;
            M << all[i].A[j].prior << endl;
        }
    }
    M.close();
    M.open("comb.txt", fstream::out);
    M << prop.size() << endl;
    REP(i, prop.size())
    {
        M << prop[i].first.size() << endl;
        M << prop[i].second << endl;
        REP(j, prop[i].first.size())
            M << prop[i].first[j].first << " " << prop[i].first[j].second << endl;
    }
    M.close();
    cout << "Thanks for visiting our restaurant\n";
    return 0;
}

