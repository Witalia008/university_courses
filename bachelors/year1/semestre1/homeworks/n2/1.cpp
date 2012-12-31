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

fstream users;

bool not_char(char a)
{
    return (a != '_' && a != '/' && !(a >= '0' && a <= '9') && !(a >= 'a' && a <= 'z') && !(a >= 'A' && a <= 'Z'));
}
bool is_not_name (string a)
{
    if (a == "-") return false;
    REP(i, a.length())
        if (not_char(a[i]))
            return true;
    return false;
}

bool is_not_phone (string s)
{
    if (s == "NO") return false;
    if (s[0] == '+') s.erase(0, 1);
    if (s.length() != 12) return true;
    REP(i, s.length())
        if (!(s[i] >= '0' && s[i] <= '9'))
            return true;
    return false;
}

bool is_not_mail (string a)
{
    if (a == "-") return false;
    int pos = -1;
    REP(i, a.length())
        if (a[i] == '@' && pos == -1)
            pos = i;
        else if (a[i] == '@')
            return true;
    if (pos <= 0) return true;
    int p1 = pos;
    FOR(i, pos + 1, a.length()-1)
        if (a[i] == '.')
            p1 = i;
    if (p1 == a.length()-1 || p1 <= pos + 1) return true;
    REP(i, a.length())
        if (not_char(a[i]) && a[i] != '.' && a[i] != '@')
            return true;
    return false;
}

struct Adress
{
    string street, name, house, flat;
    void outCMD ()
    {
        cout << street << " " << name << " ";
        cout << house << ", flat: " << flat << endl;
    }
    void outInFile (fstream &f)
    {
        f << street << " " << name << " ";
        f << house << " , flat: " << flat << endl;
    }
    void fromFile ()
    {
        users >> street >> name >> house;
        users >> flat >> flat >> flat;
    }
    void GetAdress ()
    {
        cout << "Enter type of street\n";
        cin >> street;
        while (is_not_name(street) && street != "-")
        {
            cout << "Not valid name of street, enter again\n";
            cin >> street;
        }
        cout << "Enter name of street. Use '_' instead of ' '\n";
        cin >> name;
        while (is_not_name(name) && name != "-")
        {
            cout << "Not valid name of street, enter again\n";
            cin >> name;
        }
        cout << "Enter number of house and flat\n";
        cin >> house >> flat;
    }
    bool operator == (Adress b)
    {
        if (b.street != street && street != "-" && b.street != "-") return false;
        if (b.name != name && name != "-" && b.name != "-") return false;
        if (b.house != house && house != "-" && b.house != "-") return false;
        if (b.flat != flat && flat != "-" && b.flat != "-") return false;
        return true;
    }
    bool operator != (Adress b)
    {
        return !(*this == b);
    }
};

struct Human
{
    string name, surname, phone, e_mail;
    Adress adress;
    void outCMD ()
    {
        cout << name << " " << surname << endl;
        cout << phone << endl;
        cout << e_mail << endl;
        adress.outCMD();
        cout << endl;
    }
    void outInFile (fstream &f)
    {
        f << name << " " << surname << endl;
        f << phone << endl;
        f << e_mail << endl;
        adress.outInFile(f);
    }
    void fromFile ()
    {
        users >> name >> surname;
        users >> phone;
        users >> e_mail;
        adress.fromFile();
    }
    void Get_Profile ()
    {
        cout << "Enter your name. It should consists of such symbols: _, a-z, A-Z, 0-9\n";
        cin >> name;
        while (is_not_name(name) && name != "-")
        {
            cout << "Not valid name. Enter, please, one time more.\n";
            cin >> name;
        }
        cout << "Enter your surname. It should consists of such symbols: _, a-z, A-Z, 0-9\n";
        cin >> surname;
        while (is_not_name(surname) && surname != "-")
        {
            cout << "Not valid surname. Enter, please, one time more.\n";
            cin >> surname;
        }
        cout << "Enter your phone number of 'NO' if you haven't.\n";
        cin >> phone;
        while (is_not_phone(phone) && phone != "-")
        {
            cout << "Not valid phone number. Enter, please, one time more.\n";
            cin >> phone;
        }
        cout << "Enter your e-mail.\n";
        cin >> e_mail;
        while (is_not_mail(e_mail) && e_mail != "-")
        {
            cout << "Not valid e-mail adress\n";
            cin >> e_mail;
        }
        cout << "Enter your adress\n";
        adress.GetAdress();
    }
    bool operator == (Human b)
    {
        if (b.adress != adress) return false;
        if (b.e_mail != e_mail && e_mail != "-" && b.e_mail != "-") return false;
        if (b.name != name && name != "-" && b.name != "-") return false;
        if (b.phone != phone && phone != "-" && b.phone != "-") return false;
        if (b.surname != surname && surname != "-" && b.surname != "-") return false;
        return true;
    }
    bool operator != (Human b)
    {
        return !(*this == b);
    }
};

vector<Human> all, cur;

void find_el (Human a)
{
    vector<Human> al;
    if (cur.size()) al = cur;
    else al = all;
    cur.clear();
    REP(i, al.size())
        if (al[i] == a)
            cur.pb(al[i]);
}

void del_el(Human a)
{
    cur.clear();
    REP(i, all.size())
        if (all[i] != a)
            cur.pb(all[i]);
    all.assign (cur.begin(), cur.end());
}

void manual()
{
    cout << "Go to hell\n";
}

void change (Human a, Human b)
{
    REP(i, all.size())
        if (all[i] == a)
        {
            if (b.e_mail != "-") all[i].e_mail = b.e_mail;
            if (b.name != "-") all[i].name = b.name;
            if (b.surname != "-") all[i].surname = b.surname;
            if (b.phone != "-") all[i].phone = b.phone;
            if (b.adress.name != "-") all[i].adress.name = b.adress.name;
            if (b.adress.street != "-") all[i].adress.street = b.adress.street;
            if (b.adress.flat != "-") all[i].adress.flat = b.adress.flat;
            if (b.adress.house != "-") all[i].adress.house = b.adress.house;
        }
}

#define ONLINE_JUDGE
int main ()
{
    #ifndef ONLINE_JUDGE
        freopen ("input.txt", "r", stdin);
        freopen ("output.txt", "w", stdout);
    #endif
    Human a;
    string s;
    all.clear();
    users.open("users.txt", fstream::in);
    while (!users.eof())
    {
        a.fromFile();
        all.pb(a);
    }
    users.close();
    all.pop_back();
    manual();
    for (cin >> s; s != "exit"; cin >> s)
    {
        if (s == "enter")
        {
            a.Get_Profile();
            cout << "OK\n";
        } else if (s == "reg")
        {
            //a.outInFile();
            all.push_back (a);
            cout << "succesfully registered\n";
        } else if (s == "find")
        {
            find_el(a);
            REP(i, cur.size())
                cur[i].outCMD();
        } else if (s == "erase")
        {
            find_el(a);
            bool fl = false;
            if (cur.size() == 0)
                cout << "Nothing to do there\n";
            else if (cur.size() == 1)
                fl = true;
            else {
                cout << "There are more than one valiable element. Do you want to delete anyway? [Yes/No]\n";
                cin >> s;
                REP(i, s.length())
                    if (s[i] >= 'A' && s[i] <= 'Z')
                        s[i] += 'a' - 'A';
                if (s == "yes") fl = true;
            }
            if (fl == true)
            {
                cout << "deleted " << cur.size() << " elements\n";
                del_el(a);
            }
        } else if (s == "out")
        {
            if (cur.size() == 0)
                cout << "Nothing to do there\n";
            else {
                cout << "Enter name of file\n";
                string fname;
                cin >> fname;
                fstream f(fname.c_str(), fstream::out);
                REP(i, cur.size())
                    cur[i].outInFile(f);
                f.close();
                cout << "done.\n";
            }
        } else if (s == "upd")
        {
            if (cur.size() != 1)
                cout << "Too easy. Can't do it.\n";
            else {
                change(cur[0], a);
                cout << "done.\n";
            }
        } else if (s == "man")
        {
            manual();
        }
    }
    users.open("users.txt", fstream::out);
    REP(i, all.size())
        all[i].outInFile(users);
    users.close();
    return 0;
}
