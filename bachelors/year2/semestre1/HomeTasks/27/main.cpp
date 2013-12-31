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


using namespace std;
using namespace std::chrono;

struct Graph {
    int n, m, t;//number of vertices, current m-number and current t-number
    vector<int> M, T;//M- and T- numers for each vertex
    vector<vector<int>> g, gr;//adjacency list for grapg g, gr = g^-1
    vector<int> comp, order;//current component of strong adjacenct, top-order
    vector<bool> used;//was visited or not?
};

void dfs1(int v, Graph &g) {
    g.used[v] = true;
    g.M[v] = g.m++;
    for (int to : g.g[v])
    if (!g.used[to])
        dfs1(to, g);
    g.order.push_back(v);
}

void dfs2(int v, Graph &g) {
    g.used[v] = true;
    g.comp.push_back(v);
    for (int to : g.gr[v])
    if (!g.used[to])
        dfs2(to, g);
}

void M_and_T(Graph &g) {
    g.M.resize(g.n);
    g.T.resize(g.n);
    g.order.clear();
    g.used.assign(g.n, false);
    g.m = 0;
    for (int i = 0; i < g.n; ++i)
    if (!g.used[i])
        dfs1(i, g);
    g.used.assign(g.n, false);
    g.t = 0;
    for (int i = 0; i < g.n; ++i) {
        int v = g.order[g.n - 1 - i];
        if (!g.used[v]) {
            g.T[v] = g.t++;
            g.comp.clear();
            dfs2(v, g);
            for (int j : g.comp)
            if (j != v)
                g.T[j] = g.t++;
        }
    }
}

//#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    Graph g;
    cin >> g.n >> g.m;
    g.g.resize(g.n);
    g.gr.resize(g.n);
    for (int i = 0; i < g.m; ++i) {
        int u, v;
        cin >> u >> v;
        g.g[u].push_back(v);
        g.gr[v].push_back(u);
    }
    M_and_T(g);
    for (int i = 0; i < g.n; ++i)
        cout << i << " " << g.M[i] << " " << g.T[i] << endl;
    return 0;
}