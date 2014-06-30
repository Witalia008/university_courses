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

const int N = 100005;
const int K = 505;
const ll InfL = 1000000000000000000LL;
const int MOD = 1000000007;

class Singleton {
    static Singleton* president;
    static mutex mtx;
    Singleton() {}
public:
    static Singleton* getInstance() {
        mtx.lock();
        if (president == nullptr) {
            president = new Singleton();
            cout << "Created instance\n";
        }
        mtx.unlock();
        return president;
    }
};
mutex Singleton::mtx;
Singleton* Singleton::president = nullptr;


#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    thread x = thread([]() { Singleton::getInstance(); });
    thread y = thread([]() { Singleton::getInstance(); });
    x.join(); y.join();
    system("pause");
    return 0;
}