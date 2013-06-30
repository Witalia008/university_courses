#include <iostream>
#include <memory.h>
#include <stdio.h>
#include <cstdlib>
#include <cctype>
#include <vector>

using namespace std;

const int N = 20;

int n;
int M[N][N];

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> M[i][j];
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                M[i][j] |= M[i][k] & M[k][j];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << M[i][j] << " ";
        cout << endl;
    }
    return 0;
}
