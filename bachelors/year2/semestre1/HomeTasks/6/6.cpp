#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <limits.h>
#include <algorithm>
#include <iterator>

using namespace std;

template<class T>
T Abs(T a) { return a < 0 ? -a : a; }

//swap 'times' times coins with:
//flag == true: reversive heads and non-reversive tails
//flag == false: vice versa
void change(vector<bool> a, vector<bool>& b, int times, int flag) {
    int x = times, y = times;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != (b[i] ^ flag) && (b[i] && x || !b[i] && y)) {
            if (b[i]) --x; else --y;
            b[i] = !b[i];
        }
    }
}

void process(int n, int m, int s, int k, int l) {
    if (n + m == 0) {
        cout << "Wrong data\n";
        return;
    }
    vector<bool> a;
    a.assign(n + m, false);
    //find out if i-th cell changes it's state after k steps
    //make k steps and on each step reverse one coin
    for (int i = 1; i <= k; i++)
        a[(s * i - 1) % (n + m)] = !a[(s * i - 1) % (n + m)];
    //make first coin tails
    --n;
    l -= !a[0];
    a.erase(a.begin());
    k = n + m - l;
    vector<bool> b(n + m);//1 - heads, 0 - tails
    //make first n heads, last m - tails
    for (int i = 0; i < m; ++i)
        b[n + i] = true;
    //count final number of heads and tails, and initial number of heads and tails, which will be reversed
    int heads, tails, heads_c, tails_c;
    heads = heads_c = tails = tails_c = 0;
    for (int i = 0; i < n + m; ++i) {
        if (b[i] ^ a[i]) ++heads;
        else ++tails;
        if (a[i]) {
            if (b[i]) ++heads_c;
            else ++tails_c;
        }
    }
    //swapping two different coins with different reversive flags will make one coins two more, another - two less
    if (Abs(heads - k) != Abs(tails - l) || Abs(heads - k) % 2 ||
        (heads < k && min(heads_c, tails - heads_c) < (k - heads) / 2) ||
        (tails < l && min(tails_c, heads - tails_c) < (l - tails) / 2)) {
        cout << "Impossible!\n";
        return;
    }
    //change some of them
    if (heads < k) {
        change(a, b, (k - heads) / 2, true);
    } else if (tails < l) {
        change(a, b, (l - tails) / 2, false);
    }
    cout << "0 ";
    copy(b.begin(), b.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m, k, s, l;
    cin >> n >> m >> s >> k >> l;
    process(n, m, s, k, l);
    return 0;
}
