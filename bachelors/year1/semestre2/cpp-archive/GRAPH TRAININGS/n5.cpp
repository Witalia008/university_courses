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

int n, en;
map<string, int> M;
vector<int> g[N];
string names[N];
bool used[N];
int st[N];
int top;
bool u1[N];

void dfs(int v) {
    u1[v] = true;
    used[v] = true;
    st[top++] = v;
    for (int i = 0; i < g[v].size(); i++) {
        int to = g[v][i];
        if (used[to]) {
            int k = top - 1;
            while (st[k] != to) k--;
            for (int j = k; j < top; j++) {
                cout << names[st[j] - 1] << " ";
            }
            cout << endl;
        } else {
            dfs(to);
        }
    }
    used[v] = false;
    st[--top] = -1;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++) {
        int ni;
        string name;
        cin >> name;
        cin >> ni;
        if (!M[name]) {
            M[name] = ++en;
            names[en - 1] = name;
        }
        int v = M[name];
        for (int j = 0; j < ni; j++) {
            string to;
            cin >> to;
            if (!M[to]) {
                M[to] = ++en;
                names[en - 1] = to;
            }
            g[v].push_back(M[to]);
        }
    }
    memset(st, -1, sizeof(st));
    for (int i = 1; i <= n; i++)
        if (!u1[i])
            dfs(i);
    return 0;
}
