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


using namespace std;
using namespace std::chrono;

struct Graph {
    int n, m;
    vector<vector<int>> g;
    vector<int> N;
    vector<bool> used;
    int _time;
};

void readGraph(Graph &g) {
    cin >> g.n >> g.m;
    g.g.resize(g.n);
    for (int i = 0; i < g.m; ++i) {
        int u, v;
        cin >> u >> v;
        g.g[u].push_back(v);
    }
}

void dfs(int v, Graph &g) {
    g.used[v] = true;
    for (int j : g.g[v])
        if (!g.used[j])
            dfs(j, g);
    g.N[v] = g._time--;
}

pair<int, int> start_and_finish(Graph &g) {
    vector<pair<bool, bool>> prop(g.n, make_pair(true, true));
    for (int i = 0; i < g.n; ++i) {
        if (g.g[i].size()) {
            prop[i].second = false;
            for (int j : g.g[i])
                prop[j].first = false;
        }
    }
    pair<int, int> res(0, 0);
    for (int i = 0; i < g.n; ++i) {
        res.first += prop[i].first;
        res.second += prop[i].second;
    }
    return res;
}

bool is_ordered(Graph &g){
    for (int i = 0; i < g.n; ++i) {
        for (int j : g.g[i]) {
            if (g.N[j] < g.N[i])
                return false;
        }
    }
    return true;
}

bool is_linear(Graph &g) {
    g.N.assign(g.n, 0);
    g._time = g.n;
    g.used.assign(g.n, false);
    dfs(0, g);
    return g._time == 0 && start_and_finish(g) == make_pair(1, 1) && is_ordered(g);
}

//#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    Graph g;
    readGraph(g);
    cout << is_linear(g) << endl;
    return 0;
}