#include <iostream>
#include <memory.h>
#include <stdio.h>
#include <cstdlib>
#include <cctype>
#include <vector>

using namespace std;

const int N = 20;
const int M = 200;

int n, m;
int M0[N][N];
int M1[N][M];
vector<int> adj[N];
pair<int, int> A[M];

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> A[i].first >> A[i].second;
        M0[A[i].first][A[i].second]++;
        M1[A[i].first][i] = 1;
        M1[A[i].second][i] = -1;
        adj[A[i].first].push_back(A[i].second);
    }
    return 0;
}
