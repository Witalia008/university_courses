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
    int n, m;//number of verteices and edges
    vector<vector<int>> g, gr;//adjacency luist for grapg g, and gr - g^-1
    vector<int> order, comp;//top-order of vertices, vertices ins current component of strong anjacency
    vector<bool> used;//was vertex visited or not?
};

void dfs1(int v, Graph&g) {
    g.used[v] = true;
    for (int i : g.g[v])
    if (!g.used[i])
        dfs1(i, g);
    g.order.push_back(v);
}

void dfs2(int v, Graph &g) {
    g.used[v] = true;
    g.comp.push_back(v);
    for (int i : g.gr[v])
    if (!g.used[i])
        dfs2(i, g);
}

void bicomps(Graph &g) {
    g.used.assign(g.n, false);
    g.order.clear();
    for (int i = 0; i < g.n; ++i)
    if (!g.used[i])
        dfs1(i, g);
    g.used.assign(g.n, false);
    for (int i = g.n - 1; i >= 0; --i)
    if (!g.used[i]) {
        g.comp.clear();
        dfs2(i, g);
        copy(g.comp.begin(), g.comp.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
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
    bicomps(g);
    return 0;
}