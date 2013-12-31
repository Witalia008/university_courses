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
const int GENERS_NUM = 100;
const int GENERS_CNT = 100;
const double MUTATION_PROB = 0.2;

struct Graph {
    int n, m;
    vector<vector<int>> M;
    vector<int> path_opt;
};

void read(Graph &g) {
    /*cin >> g.n >> g.m;
    g.M.resize(g.n);
    for (int i = 0; i < g.n; ++i) {
        g.M[i].assign(g.n, Inf);
        g.M[i][i] = 0;
    }
    for (int i = 0; i < g.m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g.M[u][v] = g.M[v][u] = w;
    }*/
    cin >> g.n;
    g.M.resize(g.n);
    for (int i = 0; i < g.n; ++i) {
        g.M[i].resize(g.n);
        for (int j = 0; j < g.n; ++j) {
            cin >> g.M[i][j];
        }
    }
}

ll pathLen(vector<int> path, Graph &g) {
    ll res = 0;
    for (int i = 0; i < path.size(); ++i)
        res += g.M[path[i]][path[(i + 1) % path.size()]];
    return res;
}

vector<int> randGener(int n) {
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        a[i] = i;
    random_shuffle(a.begin(), a.end());
    return a;
}

vector<vector<int>> initGeners(int n) {
    vector<vector<int>> res;
    for (int i = 0; i < GENERS_CNT; ++i)
        res.emplace_back(randGener(n));
    return res;
}

vector<vector<int>> getBest(vector<vector<int>> old, vector<pair<int, int>> seq) {
    vector<vector<int>> res;
    for (int i = 0; i < GENERS_CNT / 2; ++i)
        res.push_back(old[seq[i].second]);
    return res;
}

vector<int> crosseng(vector<int> fst, vector<int> lst) {
    vector<int> res(fst.begin(), fst.begin() + fst.size() / 2);
    for (int i = 0; i < lst.size(); ++i) {
        if (find(res.begin(), res.end(), lst[i]) == res.end())
            res.push_back(lst[i]);
    }
    return res;
}

vector<vector<int>> getNewGener(vector<vector<int>> geners) {
    int n = geners[0].size();
    vector<vector<int>> res;
    for (int i = 0; i < GENERS_CNT; ++i) {
        int u = rand() & n, v;
        do {
            v = rand() % n;
        } while (u == v);
        res.push_back(crosseng(geners[u], geners[v]));
    }
    return res;
}

void mutate(vector<vector<int>> &gen) {
    int n = gen[0].size();
    for (int i = 0; i < gen.size(); ++i) {
        if (rand() < RAND_MAX * MUTATION_PROB) {
            int u = rand() % n, v;
            do {
                v = rand() % n;
            } while (u == v);
            swap(gen[i][u], gen[i][v]);
        }
    }
}

int getBest(vector<vector<int>> geners, Graph &g) {
    int res = -1;
    ll res_l = Inf;
    for (int i = 0; i < geners.size(); ++i) {
        ll c_l = pathLen(geners[i], g);
        if (res == -1 || c_l < res_l) {
            res_l = c_l;
            res = i;
        }
    }
    return res;
}

void findSmallestPath(Graph &g) {
    vector<vector<int>> geners = initGeners(g.n);
    for (int t = 0; t < GENERS_CNT; ++t) {
        vector<pair<int, int>> seq;
        for (int i = 0; i < geners.size(); ++i)
            seq.push_back(make_pair(pathLen(geners[i], g), i));
        sort(seq.begin(), seq.end());

        geners = getBest(geners, seq);
        geners = getNewGener(geners);
        mutate(geners);
    }
    g.path_opt = geners[getBest(geners, g)];
}

void output(Graph &g) {
    cout << pathLen(g.path_opt, g) << endl;
    copy(g.path_opt.begin(), g.path_opt.end(), ostream_iterator<int>(cout, " "));
}

//#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    Graph g;
    read(g);
    findSmallestPath(g);
    output(g);
    return 0;
}