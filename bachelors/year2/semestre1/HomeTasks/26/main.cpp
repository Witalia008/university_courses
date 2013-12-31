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
    unordered_map<string, int> dict;//dictionary of words with their number in input
    vector<string> all;//vector of all words in lexicographical order
    vector<vector<int>> adj;//adjacency list
    vector<int> order;//top-order of vertices
    vector<bool> used;//was visited or not?
    vector<int> max_l, par;//maximal length of ladder for current position, par - from which word we came to current one?
};

string change_at(string s, int pos, char wh) {
    if (pos < 0 || pos >= s.size())
        return "";
    s[pos] = wh;
    return s;
}

string add_at(string s, int pos, char wh) {
    if (pos < 0 || pos > s.size())
        return "";
    s.insert(s.begin() + pos, wh);
    return s;
}

void try_add(string a, string b, Graph &g) {
    if (g.dict[a] != 0 && g.dict[b] != 0 && b > a) {
        int u = g.dict[a] - 1;
        int v = g.dict[b] - 1;
        g.adj[u].push_back(v);
    }
}

void build_graph(Graph &g) {
    g.adj.resize(g.dict.size());
    for (string s : g.all) {
        for (char i = 'a'; i <= 'z'; ++i) {
            for (int j = 0; j <= s.size(); ++j) {
                try_add(s, change_at(s, j, i), g);
                try_add(s, add_at(s, j, i), g);
            }
        }
    }
}

void dfs(int v, Graph &g) {
    g.used[v] = true;
    for (int to : g.adj[v])
    if (!g.used[to])
        dfs(to, g);
    g.order.push_back(v);
}

void top_sort(Graph &g) {
    g.used.assign(g.all.size(), false);
    for (int i = 0; i < g.all.size(); ++i)
    if (!g.used[i])
        dfs(i, g);
    reverse(g.order.begin(), g.order.end());
}

int max_ladder(Graph &g) {
    g.max_l.assign(g.all.size(), 1);
    g.par.assign(g.all.size(), -1);
    int res = g.order[0];
    for (int i : g.order) {
        for (int to : g.adj[i]) {
            if (g.max_l[to] < g.max_l[i] + 1) {
                g.max_l[to] = g.max_l[i] + 1;
                g.par[to] = i;
            }
        }
        if (g.max_l[i] > g.max_l[res])
            res = i;
    }
    return res;
}

void output_ladder(int v, Graph &g) {
    vector<string> res;
    do {
        res.push_back(g.all[v]);
        v = g.par[v];
    } while (v != -1);
    copy(res.rbegin(), res.rend(), ostream_iterator<string>(cout, "\n"));
}

//#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    Graph g;
    g.all = vector<string>(istream_iterator<string>(cin), istream_iterator<string>());
    for (int i = 0; i < g.all.size(); ++i)
        g.dict[g.all[i]] = i + 1;
    build_graph(g);
    top_sort(g);
    int target = max_ladder(g);
    output_ladder(target, g);
    return 0;
}