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

enum class RibType { Forth, Back, Cross, Tree };

struct Graph {
    int n, m;//number of vertices and edges
    vector<pair<int, int>> ribs;//all edges, pair of (from, to)
    vector<vector<pair<int, int>>> g;//list of adjacence for each vertex (pair (to, rib id))
    vector<bool> used;//was vertex visited by dfs or not?
    vector<RibType> types;//type of rib in dfs tree
    vector<vector<int>> domin;//for each vertex holds set of vertices, that dominate over it
    vector<int> color;//color of vertex
    vector<int> tin, tout;//in and out time in dfs
    int _time;//cur time
};

void dfs(int v, bool fl, Graph &g) {
    g.used[v] = fl;
    for (auto to : g.g[v])
    if (g.used[to.first] != fl)
        dfs(to.first, fl, g);
}

vector<int> Alt(int v, Graph &g) {
    vector<int> res;
    g.used.assign(g.n, false);
    dfs(v, true, g);
    g.used[v] = false;
    for (int i = 0; i < g.n; ++i)
    if (!g.used[i] && i != v)
        dfs(i, false, g);
    g.used[v] = true;
    for (int i = 0; i < g.n; ++i)
    if (g.used[i])
        res.push_back(i);
    return res;
}

void dominance(Graph &g) {
    g.domin.resize(g.n);
    for (int i = 0; i < g.n; ++i) {
        vector<int> alt = Alt(i, g);
        for (int j : alt)
            g.domin[j].push_back(i);
    }
}

void DFST(int v, Graph &g) {
    g.tin[v] = ++g._time;
    g.color[v] = 1;
    for (auto to : g.g[v]) {
        if (g.color[to.first] == 0) {
            g.types[to.second] = RibType::Tree;
            DFST(to.first, g);
        }
        else if (g.color[to.first] == 1) {
            g.types[to.second] = RibType::Back;
        }
        else if (g.color[to.first] == 2) {
            if (g.tout[to.first] < g.tin[v])
                g.types[to.second] = RibType::Cross;
            else
                g.types[to.second] = RibType::Forth;
        }
    }
    g.color[v] = 2;
    g.tout[v] = ++g._time;
}

bool isReduceble(Graph &g) {
    dominance(g);

    g.color.assign(g.n, 0);
    g.types.resize(g.m);
    g._time = 0;
    g.tin.assign(g.n, 0);
    g.tout.assign(g.n, 0);
    DFST(0, g);

    for (int i = 0; i < g.m; ++i)
    if (g.types[i] == RibType::Back) {
        int u = g.ribs[i].first, v = g.ribs[i].second;
        if (find(g.domin[u].begin(), g.domin[u].end(), v) == g.domin[u].end())
            return false;
    }
    return true;
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
    g.ribs.resize(g.m);
    for (int i = 0; i < g.m; ++i) {
        cin >> g.ribs[i].first >> g.ribs[i].second;
        g.g[g.ribs[i].first].push_back(make_pair(g.ribs[i].second, i));
    }
    cout << isReduceble(g) << endl;
    return 0;
}