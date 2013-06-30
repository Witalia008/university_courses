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

const int Inf = 10e9;
const int Mi = Inf + 7;
const int N = 105;
const int K = 32;
const ld eps = 10e-7;
const ld PI = 2 * acos(0.0);
const ll InfLL = ll(Inf) * ll(Inf);

inline ll gcd (ll a, ll b){ return (!b ? a : gcd (b, a % b)); }

int rand15() { return rand() % (1 << 15); }
int rand30() { return (rand15() << 15) + rand15(); }
int rand(int L, int R) { if (L > R) return R; return rand30() % (R - L + 1) + L; }
ld random(ld L, ld R) { return rand(ceil((L-eps)*100), floor((R+eps)*100)) / 100.0;}


//#define DEBUG

struct TBtree {
    int num;
    TBtree *l, *r;
};

struct BT {
    bool is_l, is_r;
    BT *l, *r;
    int num;
};

typedef unsigned int uni;

deque<int> sons[N];
TBtree *bt[N];
int n;

TBtree *to_binary(deque<int> all) {
    if (all.size() == 0) {
        return NULL;
    }
    TBtree *res = new TBtree();
    res->num = all[0];
    bt[all[0]] = res;
    res->l = to_binary(sons[all[0]]);
    all.pop_front();
    res->r = to_binary(all);
    return res;
}

void from_binary(TBtree *v, int p = -1) {
    if (p != -1 && v->r != NULL) {
        sons[p].push_back(v->r->num);
    }
    if (v->l == NULL) {
        return;
    }
    sons[v->num].push_back(v->l->num);
    REP(i, sons[v->num].size()) {
        from_binary(bt[sons[v->num][i]], v->num);
    }
}

BT *firmware(TBtree *v, BT *prev = NULL, BT *next = NULL) {
    BT *res = new BT();
    res->num = v->num;
    if (v->l != NULL) {
        res->is_l = true;
        res->l = firmware(v->l, prev, res);
    } else {
        res->is_l = false;
        res->l = prev;
    }
    if (v->r != NULL) {
        res->is_r = true;
        res->r = firmware(v->r, res, next);
    } else {
        res->is_r = false;
        res->r = next;
    }
    return res;
}

void trav(TBtree *t, int p = 0) {
    vector<TBtree*> father, son;
    father.push_back(t);
    while (father.empty() == false) {
        son.clear();
        for (int i = 0; i < father.size(); i++) {
            if (father[i] == NULL) {
                cout << 0 << " ";
                continue;
            }
            cout << father[i]->num << " ";
            //if (father[i]->l != NULL) {
                son.push_back(father[i]->l);
            //}
            //if (father[i]->r != NULL) {
                son.push_back(father[i]->r);
            //}
        }
        father.swap(son);
        cout << endl;
    }
    /*if (t == NULL) {
        return;
    }
    trav(t->l, t->num);
    cout << p << " " << t->num << "\n";
    trav(t->r, t->num);*/
}


BT *get_first_one(BT *v) {
    while (v->is_l == true) {
        v = v->l;
    }
    return v;
}

void traverse(BT *v) {
    v = get_first_one(v);
    while (v != NULL) {
        cout << v->num << " ";
        if (v->is_r) {
            v = get_first_one(v->r);
        } else {
            v = v->r;
        }
    }
}

//#define DEBUG_MODE
//#define ONLINE_JUDGE
int main ()
{
    std::ios_base::sync_with_stdio(0);
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int root = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int p;
        cin >> p;
        sons[p].push_back(i);
    }
    TBtree *r = to_binary(sons[0]);
    trav(r);
    cout << endl;
    for (int i = 1; i <= n; i++)
        sons[i].clear();
    from_binary(r);
    for (int i = 0; i <= n; i++) {
        for (int i = 0; i < sons[i].size(); i++){
            cout << sons[i][j] << " ";
        }
        cout << endl;
    }
    BT *rr = firmware(r);
    traverse(rr);
    return 0;
}
