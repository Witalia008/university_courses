#define _CRT_SECURE_NO_WARNINGS
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

#define Cpp11
#ifdef Cpp11
#include <cassert>
#include <chrono>
#include <regex>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <valarray>
using namespace std::chrono;
#endif
using namespace std;

typedef double ld;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

//const int mx[4] = { 1, 0, -1, 0 };
//const int my[4] = { 0, 1, 0, -1 };

const int Inf = 1000000000;
const int Mi = 1000000007;
const int N = 500005;
const int M = 100005;
//const int K = 20;
const ld eps = 10e-7;
const ld PI = 2 * acos(0.0);
const ll InfLL = ll(Inf) * ll(Inf);

unsigned rand16() { return rand() % (1 << 16); }
unsigned rand32() { return (rand16() << 16) + rand16(); }
ull rand64() { return (((ull)rand32()) << 32) + rand32(); }
int rand(int L, int R)
{
    if (L > R)
        return R;
    return rand32() % (R - L + 1) + L;
}
ld random(ld L, ld R) { return rand(ceil((L - eps) * 100), floor((R + eps) * 100)) / 100.0; }

ll Abs(ll a) { return a < 0 ? -a : a; }
ll sqr(ll a) { return a * a; }
ll gcd(ll a, ll b) { return !b ? a : gcd(b, a % b); }

string toStr(int n)
{
    char s[100];
    sprintf(s, "%d", n);
    return string(s);
}

typedef vector<unordered_map<int, int>> vom_ii;
typedef vector<unordered_set<int>> vos_i;

struct Automata
{
    int n = 0;
    vom_ii adj;
    vvi adj_inv;
};

vector<vos_i> R_rang(Automata &A)
{
    vector<vos_i> res;
    res.push_back({{}});
    vector<int> used(A.n, 0);
    for (int i = 0; i < A.n; ++i)
    {
        for (int to : A.adj_inv[i])
        {
            ++used[to];
        }
    }
    for (int i = 0; i < A.n; ++i)
    {
        if (used[i] == 0)
        {
            res.back()[0].insert(i);
            used[i] = -1;
        }
    }
    for (int i = 0; i < res.size(); ++i)
    {
        res.push_back({{}});
        for (int j : res[i][0])
        {
            for (auto to : A.adj_inv[j])
            {
                --used[to];
                if (used[to] == 0)
                {
                    res.back()[0].insert(to);
                    used[to] = -1;
                }
            }
        }
        if (res.back()[0].size() == 0)
        {
            res.pop_back();
        }
    }
    return res;
}

Automata convert_toA(vector<vos_i> R, Automata &A)
{
    Automata B;
    vector<int> comp(A.n);
    for (int i = 0; i < R.size(); ++i)
    {
        for (int j = 0; j < R[i].size(); ++j)
        {
            for (int a : R[i][j])
            {
                comp[a] = B.n;
            }
            ++B.n;
        }
    }
    B.adj.resize(B.n);
    for (int i = 0; i < R.size(); ++i)
    {
        for (int j = 0; j < R[i].size(); ++j)
        {
            for (int a : R[i][j])
            {
                for (auto to : A.adj[a])
                {
                    //if (comp[a] != comp[to.second]) {
                    B.adj[comp[a]][to.first] = comp[to.second];
                    //}
                }
            }
        }
    }
    return B;
}

Automata MAA(Automata &A)
{
    vector<vos_i> R = R_rang(A);
    for (int k = 0; k < R.size(); ++k)
    { // for all K from R wrt increasing
        for (int kk = 0; kk < R[k].size(); ++kk)
        {

            for (int l = k + 1; l < R.size(); ++l)
            { // for all L from R suck that L > K
                int Rl_sz = R[l].size();
                for (int ll = 0; ll < Rl_sz; ++ll)
                {

                    for (int x = 'a'; x <= 'z'; ++x)
                    { // for all x in X

                        unordered_set<int> L_in, L_out;
                        for (int a : R[l][ll])
                        {
                            if (A.adj[a].find(x) != A.adj[a].end() && R[k][kk].find(A.adj[a][x]) != R[k][kk].end())
                            {
                                L_in.insert(a);
                            }
                            else
                            {
                                L_out.insert(a);
                            }
                        }
                        if (L_in.size() && L_out.size())
                        {
                            R[l][ll] = L_in;
                            R[l].push_back(L_out);
                        }
                    }
                }
            }
        }
    }
    return convert_toA(R, A);
}

//#define ONLINE_JUDGE
int main()
{
    std::ios_base::sync_with_stdio(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    Automata A;
    int m;
    cin >> A.n >> m;
    A.adj.resize(A.n);
    A.adj_inv.resize(A.n);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        char w;
        cin >> u >> v >> w;
        A.adj[u - 1][w] = v - 1;
        A.adj_inv[v - 1].push_back(u - 1);
    }
    Automata B = MAA(A);

    cout << B.n << endl;
    for (int i = 0; i < B.n; ++i)
    {
        for (auto to : B.adj[i])
        {
            cout << (B.n - i) << " " << (B.n - to.second) << " " << char(to.first) << endl;
        }
    }
    return 0;
}