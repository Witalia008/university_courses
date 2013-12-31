#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <string>
#include <memory.h>
#include <map>
#define _USE_MATH_DEFINES
#include <math.h>
#include <list>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <queue>
#include <stack>
#include <complex>
#include <limits.h>
#include <cassert>
#include <chrono>
#include <regex>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <unordered_map>
#include <unordered_set>


using namespace std;
using namespace std::chrono;

#include "BTree.hpp"

#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    srand(182982);
    BTree<int> tree(2);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x = rand() % 30;
        if (rand() & 1) {
            tree.insert(x);
            cout << "+ " << x << endl;
        }
        else {
            tree.remove(x);
            cout << "- " << x << endl;
        }
    }
    cout << tree << endl;

    for (int i = 0; i < n; ++i) {
        int x = rand() % 100;
        cout << x << " " << tree.find(x) << endl;
    }
    system("pause");
    return 0;
}