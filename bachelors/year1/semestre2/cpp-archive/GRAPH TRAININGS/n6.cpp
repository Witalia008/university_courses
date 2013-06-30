#include <iostream>
#include <memory.h>
#include <stdio.h>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <queue>
#include <map>

using namespace std;

const int N = 20;
const int Inf = 1000000000;

int n, m;
int D[N][N];
int F[N][N];
vector<int> way[N][N];

void output(int u, int v) {
    if (way[u][v].size() == 0) {
        cout << u << " ";
    } else {
        for (int i = 0; i < way[u][v].size(); i++) {
            output(u, way[u][v][i]);
            output(way[u][v][i], v);
            cout << v << endl;
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            F[i][j] = D[i][j] = Inf;
            way[i][j].clear();
        }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        D[u][v] = F[u][v] = 1;
    }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (D[i][j] > D[i][k] + D[k][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    way[i][j].clear();
                }
                if (D[i][j] == D[i][k] + D[k][j]) {
                    way[i][j].push_back(k);
                }
            }
    int min_len = Inf;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            min_len = min(min_len, D[i][j] + F[j][i]);
    if (min_len != Inf) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (D[i][j] + F[j][i] == min_len) {
                    output(i, j);
                }
    }
    return 0;
}
