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
#include <random>
#include <valarray>

using namespace std;
using namespace std::chrono;

typedef long long ll;

const int N = 16005;
const int K = 605;
const ll InfL = 1000000000000000000LL;
const int MOD = 1000000007;

#include "Array.h"
#include "PeekbackStack.h"
#include "BoundedStackDerivedFromArray.h"
#include "BoundedStackAgregatingArray.h"
#include "ProtectedArray.h"
#include "CyclicArray.h"
#include "QueueFromCyclicArray.h"

#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    BoundedStackAgregatingArray<int> st(10);
    for (int i = 0; i < 10; ++i)
        st.push(rand() % 10);
    cout << st.full() << endl;
    Queue<int> q(10);
    for (int i = 0; i < 20; ++i)
        q.push(rand() % 10);
    for (int i = 0; i < 10; ++i) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
    system("pause");
    return 0;
}