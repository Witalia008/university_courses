#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <limits.h>
#include <algorithm>
#include <iterator>

using namespace std;

vector<int> dsu;
int n, m;
using pii = pair<int, int>;
vector<pii> edges;
vector<int> depth;
vector<vector<int>> adj;
vector<vector<int>> anc;

//get root of set of vertex v
int dsu_get(int v) {
    if (dsu[v] == v) return v;
    return dsu[v] = dsu_get(dsu[v]);
}

//join two set trees and return if they were in diff sets
bool dsu_join(int u, int v) {
    u = dsu_get(u);
    v = dsu_get(v);
    if (u == v) return false;
    if (rand() & 1)
        swap(u, v);
    dsu[u] = v;
    return true;
}

//stanning tree (adj will hold this tree)
void kruskal() {
    dsu.resize(n);
    adj.resize(n);
    for (int i = 0; i < n; ++i) dsu[i] = i;
    for (int i = 0; i < m; ++i) {
        if (dsu_join(edges[i].first, edges[i].second)) {
            adj[edges[i].first].push_back(edges[i].second);
            adj[edges[i].second].push_back(edges[i].first);
            edges[i] = make_pair(-1, -1);
        }
    }
}

const int K = 20;

//traverse tree and calc all ancestors
void dfs(int v, int p = -1) {
    anc[v].resize(K);
    anc[v][0] = p == -1 ? v : p;
    for (int i = 1; i < K; ++i)
        anc[v][i] = anc[anc[v][i - 1]][i - 1];
    depth[v] = p == -1 ? 0 : depth[p] + 1;
    for (int to : adj[v])
        if (to != p)
            dfs(to, v);
}

//lowest common ancestor in spanning tree
int lca(int u, int v) {
    if (depth[u] > depth[v])
        swap(u, v);
    for (int i = K - 1; i >= 0; --i)
        if (depth[anc[v][i]] >= depth[u])
            v = anc[v][i];
    if (u == v)
        return u;
    for (int i = K - 1; i >= 0; --i)
        if (anc[u][i] != anc[v][i]) {
            u = anc[u][i];
            v = anc[v][i];
        }
    return anc[u][0];
}

//cycle - path from vertex u to v through their lca
void out_cycle(int u, int v) {
    int x = lca(u, v);
    for (; u != x; u = anc[u][0])
        cout << u << " ";
    cout << x << " ";
    vector<int> a;
    for (; v != x; v = anc[v][0])
        a.push_back(v);
    reverse(a.begin(), a.end());
    copy(a.begin(), a.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

void out_all() {
    for (int i = 0; i < m; ++i)
        if (edges[i].first != -1)//if egde is not in spanning tree - out cycle with it
            out_cycle(edges[i].first, edges[i].second);
}

void find_cycles() {
    kruskal();
    anc.resize(n);
    depth.resize(n);
    dfs(0);
    out_all();
}

vector<vector<bool>> inc;

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n >> m;
    inc.resize(m);
    for (int i = 0; i < m; ++i) {
        int fr, to;
        cin >> fr >> to;
        inc[i].assign(n, false);
        inc[i][to] = inc[i][fr] = true;
    }
    for (int i = 0; i < m; ++i) {
        int fr = -1, to = -1;
        for (int j = 0; j < n; ++j)
            if (inc[i][j]) {
                if (fr == -1)
                    fr = j;
                else to = j;
            }
        edges.push_back(make_pair(fr, to));
    }
    find_cycles();
    return 0;
}
