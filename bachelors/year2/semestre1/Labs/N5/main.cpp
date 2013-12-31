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

#include "HashMap.hpp"

unordered_map<int, int> a;

HashTable<int> T;
HashMap<int, int> M;

#define ONLINE_JUDGE
int main () {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cout << "Insertion" <<endl;
    for (int i = 0; i < 20; ++i) {
        int cur_key = rand() % 10, cur_val = rand() % 10;
        cout << cur_key << " " << cur_val << " " << M.insert(make_pair(cur_key, cur_val)) << endl;
    }
    cout << "Finding" << endl;
    for (int i = 0; i < 10; ++i) {
        int cur_key = rand() % 10, cur_val = rand() % 10;
        cout << cur_key << " " << cur_val << " " << M.find(make_pair(cur_key, cur_val)) << endl;
    }
    cout << "Removing" << endl;
    for (int i = 0; i < 30; ++i) {
        int cur_key = rand() % 10, cur_val = rand() % 10;
        cout << cur_key << " " << cur_val << " " << M.remove(make_pair(cur_key, cur_val)) << endl;
    }
    system("pause");
    return 0;
}