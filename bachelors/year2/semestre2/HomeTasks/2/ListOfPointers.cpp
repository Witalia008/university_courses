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

template <class T>
class ListOfPointers {
protected:
    vector<T*> _pointers;
public:
    ListOfPointers() {}
    ListOfPointers(initializer_list<T*> lst) : _pointers(lst) {}
    void add(T *anotherPointer) {
        _pointers.push_back(anotherPointer);
    }
    void remove(T *ptr) {
        vector<T*>::iterator it;
        if ((it = find(_pointers.begin(), _pointers.end(), ptr)) != _pointers.end())
            _pointers.erase(it);
    }
    T *get(int idx) {
        if (idx < 0 || idx >= _pointers.size())
            return nullptr;
        return _pointers[idx];
    }
    void destroy() {
        for (auto i : _pointers)
            delete i;
        _pointers.clear();
    }
};

#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ListOfPointers<int> a = { new int(1), new int(2), new int(3) };
    cout << *a.get(2) << endl;
    system("pause");
    return 0;
}