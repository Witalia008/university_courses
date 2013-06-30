#include <iostream>
#include <memory.h>
#include <stdio.h>
#include <cstdlib>
#include <cctype>

using namespace std;

const int N = 20;
const int M = 200;

int n;
int adj[N][M];
int deg[N];

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n;
    for (int i = 0;; i++) {
        int u, v;
        u = v = -1;
        cin >> u >> v;
        if (u < 0) break;
        u--; v--;
        adj[u][i]++;
        adj[v][i]++;
        deg[u]++;
        deg[v]++;
    }
    for (int i = 0; i < n; i++)
        cout << deg[i] << " ";
    return 0;
}
