#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <set>
#include <algorithm>
#include <queue>
#include <map>

#include "rbtree.hpp"

using namespace std;

struct c1 {
    bool operator()(int a, int b) { return a > b; }
};

auto cmp = [](int a, int b) { return a > b; };
bool c2(int a, int b) {
    return a > b;
}
Tree<int, decltype(&c2)> t(c2);

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    for (int i = 0; i < 20; i++) {
        int x = rand() % 10;
        cout << x;
        if (t.find(x))
            cout << " - : ", t.remove(x);
        else
            cout << " + : ", t.insert(x);
        cout << t << endl;
    }
    return 0;
}
