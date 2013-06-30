/* Зауваження!
 * На орієнтованому графі не визначене поняття зв'язності,
 * тож тут реалізовано алгоритм пошуку компонент сильної(!) зв'язності.
 */

#include <iostream>
#include <memory.h>
#include <stdio.h>
#include <cstdlib>
#include <cctype>
#include <vector>

using namespace std;

const int N = 20;

int n, m;
vector<int> g[N], gr[N];
bool used[N];
vector<int> order, component;

void dfs1(int v) {
    used[v] = true;
    for (int i = 0; i < g[v].size(); i++) {
        if (!used[g[v][i]]) {
            dfs1(g[v][i]);
        }
    }
    order.push_back(v);
}

void dfs2(int v) {
    used[v] = true;
    component.push_back(v);
    for (int i = 0; i < gr[v].size(); i++) {
        if (!used[gr[v][i]]) {
            dfs2(gr[v][i]);
        }
    }
}

int D[N][N * N];

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        D[u][i] = 1;
        D[v][i] = -1;
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        for (int j = 0; j < n; j++)
            if (D[j][i] == -1)
                v = j;
            else if (D[j][i] == 1)
                u = j;
        g[u].push_back(v);
        gr[v].push_back(u);
    }
    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs1(i);
    memset(used, 0, sizeof(used));
    for (int i = n - 1; i >= 0; i--) {
        int v = order[i];
        if (!used[v]) {
            component.clear();
            dfs2(v);
            for (int j = 0; j < component.size(); j++)
                cout << component[j] << " ";
            cout << endl;
        }
    }
    return 0;
}
