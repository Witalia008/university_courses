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
    vector<vector<pair<int, int>>> g;
    unordered_map<int, pair<int, int>> all;
    vector<int> col;
};

void read(Graph &g) {
    unordered_map<int, int> ribs;
    cin >> g.n >> g.m;
    g.g.resize(g.n);
    for (int i = 0; i < 2 * g.m; ++i) {
        int x, u;
        cin >> x >> u;
        --x;
        if (ribs[x] == 0)
            ribs[x] = u;
        else {
            int v = ribs[x];
            --u; --v;
            g.g[v].push_back(make_pair(u, x));
            g.all[x] = make_pair(v, u);
        }
    }
}

bool dfs(int v, Graph &g, int mask) {
    g.col[v] = 1;
    for (auto to : g.g[v]) {
        if ((mask >> to.second) & 1) {
            if (g.col[to.first] == 1)
                return false;
            if (g.col[to.first] == 0) {
                if (!dfs(to.first, g, mask))
                    return false;
            }
        }
    }
    g.col[v] = 2;
    return true;
}

void output(int mask, Graph &g) {
    for (int i = 0; i < g.m; ++i) {
        if ((mask >> i) & 1)
            cout << g.all[i].first + 1 << " -> " << g.all[i].second + 1 << " | ";
    }
    cout << endl;
}

void search(Graph &g) {
    for (int i = 0; i < (1 << g.m); ++i) {
        bool good = true;
        g.col.assign(g.n, 0);
        for (int j = 0; j < g.n; ++j) {
            if (!g.col[j])
                good &= dfs(j, g, i);
        }
        if (good)
            output(i, g);
    }
}

//#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    Graph g;
    read(g);
    search(g);
    return 0;
}