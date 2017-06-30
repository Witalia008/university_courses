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

vector<int> prefix_function(string s)
{
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; ++i)
    {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
        {
            j = pi[j - 1];
        }
        if (s[i] == s[j])
            ++j;
        pi[i] = j;
    }
    return pi;
}

struct Trie
{
    Trie *nxt[26], *p[26];
    bool is_end;
    int depth;

    Trie()
    {
        memset(nxt, NULL, sizeof(nxt));
        memset(p, NULL, sizeof(p));
        is_end = false;
        depth = 0;
    }
};

Trie *root = new Trie();

void add(string a)
{
    Trie *v = root;
    for (char q : a)
    {
        if (v->nxt[q] == NULL)
        {
            v->nxt[q] = new Trie();
            v->nxt[q]->depth = v->depth + 1;
        }
        v = v->nxt[q];
    }
    v->is_end = true;
}

void dfs(Trie *v, Trie *p)
{
    for (int i = 0; i < 26; ++i)
    {
        if (v->nxt[i] != NULL)
        {
            v->p[i] = v->nxt[i];
        }
        else
        {
            if (p == NULL)
            {
                v->p[i] = v;
            }
            else
            {
            }
        }
    }
    for (int i = 0; i < 26; ++i)
    {
        if (v->nxt[i] != NULL)
        {
            dfs(v->nxt[i], v);
        }
    }
}

//#define ONLINE_JUDGE
int main()
{
    std::ios_base::sync_with_stdio(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    string a, b;
    cin >> a >> b;
    string s = a + '\0' + b;
    auto p = prefix_function(s);
    for (int i = a.size() << 1; i < s.size(); ++i)
    {
        if (p[i] == a.size())
        {
            cout << "(" << (i - (a.size() << 1)) << ", " << (i - a.size() - 1) << ")" << endl;
        }
    }
    add(a);
    dfs(root, NULL);
    Trie *v = root;
    for (int i = 0; i < b.size(); ++i)
    {
        v = v->nxt[b[i]];
        if (v->is_end)
        {
            cout << "(" << i << ", " << (i - v->depth + 1) << ")" << endl;
        }
    }
    return 0;
}