#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstdlib>

using namespace std;

int get_win_n(int n, int k) {
    //pn positions, true - winning, false - losing
    vector<vector<bool>> PN(n + 1);
    for (auto &i : PN)
        i.assign(k + n, false);
    PN[0].assign(k + n, true);
    for (int cur_n = 1; cur_n <= n; ++cur_n) {//current number of stones
        for (int cur_k = 0; cur_k < n - cur_n + k; ++cur_k) {//how many we could pick
            PN[cur_n][cur_k] = false;
            for (int n_pick = 0; n_pick <= cur_k && n_pick < cur_n; ++n_pick)//how many we try yo pick
                //if we get losing position after picking this number of stones - thisposition is winning
                if (PN[cur_n - 1 - n_pick][n_pick + 1] == false) {
                    PN[cur_n][cur_k] = true;
                    break;
                }
        }
    }
    for (int n_pick = 0; n_pick < k; ++n_pick)
        if (PN[n][n_pick] == true)//if picking n_pick tones gives us winning pos - output
            return n_pick + 1;
    return -1;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, k;
    cin >> n >> k;
    cout << get_win_n(n, k) << endl;
    return 0;
}
