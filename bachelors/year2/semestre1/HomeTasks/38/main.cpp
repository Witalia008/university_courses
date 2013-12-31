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


using namespace std;
using namespace std::chrono;

using ll = long long;
const int Inf = 1000000000;

struct Graph {
    int n, m;
    int s, t;
    vector<vector<int>> C, F;
    vector<int> ptr, st, d;
};

const bool by_vertex = true;

int fst(int i) {
    return i * (by_vertex + 1);
}

int lst(int i) {
    return by_vertex ? i * 2 + 1 : i;
}

int origin(int i) {
    return i / (by_vertex + 1);
}

void read(Graph &g) {
    cin >> g.n >> g.m;
    if (by_vertex)
        g.n *= 2;
    g.C.resize(g.n);
    g.F.resize(g.n);
    for (int i = 0; i < g.n; ++i) {
        g.C[i].assign(g.n, 0);
        g.F[i].assign(g.n, 0);
    }
    if (by_vertex) {
        for (int i = 0; i < g.n / 2; ++i) {
            g.C[fst(i)][lst(i)] = 1;
            g.C[lst(i)][fst(i)] = 1;
        }
    }
    for (int i = 0; i < g.m; ++i) {
        int u, v;
        cin >> u >> v;
        g.C[lst(u)][fst(v)] = 1;
        g.C[lst(v)][fst(u)] = 1;
    }
    cin >> g.s >> g.t;
    g.s = lst(g.s);
    g.t = fst(g.t);
}

bool bfs(Graph &g) {
    g.d.assign(g.n, -1);
    queue<int> q;
    g.d[g.s] = 0;
    q.push(g.s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < g.n; ++i) {
            if (g.d[i] == -1 && g.F[v][i] < g.C[v][i]) {
                g.d[i] = g.d[v] + 1;
                q.push(i);
            }
        }
    }
    return g.d[g.t] != -1;
}

int dfs(int v, int cur_flow, Graph &g) {
    if (!cur_flow)
        return 0;
    if (v == g.t)
        return cur_flow;
    for (int &to = g.ptr[v]; to < g.n; ++to) {
        if (g.d[to] != g.d[v] + 1) continue;
        int pushed = dfs(to, min(cur_flow, g.C[v][to] - g.F[v][to]), g);
        if (pushed) {
            g.F[v][to] += pushed;
            g.F[to][v] -= pushed;
            return pushed;
        }
    }
    return 0;
}

int dinic(Graph &g) {
    int flow = 0;
    while (bfs(g)) {
        g.ptr.assign(g.n, 0);
        while (int pushed = dfs(g.s, Inf, g))
            flow += pushed;
    }
    return flow;
}

bool output(int v, Graph &g) {
    g.st.push_back(origin(v));
    if (v == g.t) {
        for (int i = 0; i < g.st.size(); ++i) {
            if (!i || g.st[i] != g.st[i - 1]) {
                cout << g.st[i] << " ";
            }
        }
        cout << endl;
        g.st.pop_back();
        return true;
    }
    for (int to = 0; to < g.n; ++to) {
        if (g.F[v][to] > 0) {
            if (output(to, g)) {
                g.F[v][to]--;
                g.F[to][v]++;
                g.st.pop_back();
                return true;
            }
        }
    }
    g.st.pop_back();
    return false;
}

//#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    Graph g;
    read(g);
    cout << dinic(g) << endl;
    while (output(g.s, g));
    return 0;
}