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

class A
{
public:
    virtual ~A() {}
    string Name() {
        return DoName();
    }
private:
    virtual string DoName() {
        return "A";
    }
};

template<class T = A>
class B1 : virtual public T {
    string DoName() override {
        return "B1";
    }
};

template<class T = A>
class B2 : virtual public T {
    string DoName() override {
        return "B2";
    }
};

class D : public B2<B1<>> {
    string DoName() {
        return  "D";
    }
};

#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    A* a = new D;
    D* d = new D;
    B2<B1<A>> *b1 = new D;
    B1<> *b2 = new D;
    cout << d->Name() << endl;
    cout << a->Name() << endl;
    cout << b1->Name() << endl;
    cout << b2->Name() << endl;
    system("pause");
    return 0;
}