#include <iostream>
#include <memory.h>
#include <stdio.h>
#include <cstdlib>
#include <cctype>

using namespace std;

const int N = 20;
const int M = 200;

int n, m;
int adj[N][M];
int deg[N];

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n;
    for (m = 0;; m++) {
        int u, v;
        u = v = -1;
        cin >> u >> v;
        if (u < 0) break;
        u--; v--;
        adj[u][m]++;
        adj[v][m]++;
    }
    for (int i = 0; i < n; i++) {
        int deg = 0;
        for (int j = 0; j < m; j++)
            deg += adj[i][j];
        cout << deg << " ";
    }
    return 0;
}
