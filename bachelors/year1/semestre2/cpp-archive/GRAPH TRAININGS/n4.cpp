#include <iostream>
#include <memory.h>
#include <stdio.h>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <queue>

using namespace std;

const int N = 20;

int n, m;
vector<int> g[N];
bool used[N];
queue<int> q;

void bfs(int st) {
    q.push(st);
    used[st] = true;
    printf("Vertex %d discovered\n", st + 1);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < g[v].size(); i++) {
            int to = g[v][i];
            if (!used[to]) {
                printf("Vertex %d discovered\n", to + 1);
                q.push(to);
                used[to] = true;
            }
        }
        printf("Vertex %d explored\n", v + 1);
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        //g[v].push_back(u);
    }
    for (int i = 0; i < n; i++)
        if (!used[i])
            bfs(i);
    return 0;
}
