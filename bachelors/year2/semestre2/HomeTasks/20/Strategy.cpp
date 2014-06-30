#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <iterator>
#include <ctime>

using namespace std;

class Strategy {
public:
    Strategy(int n) {
        arr.resize(n);
        cout << "Enter " << n << " elements: ";
        for (int &i: arr)
            cin >> i;
    }
    virtual void sort(int, int) = 0;
protected:
    vector<int> arr;
};

void Strategy::sort(int l, int r) {
    for (int i: arr)
        cout << i << " ";
    cout << endl;
}

class QuickStrategy : public Strategy {
public:
    QuickStrategy(int n) : Strategy(n) {}
    void sort(int l, int r) {
        std::sort(arr.begin() + l, arr.begin() + r + 1);
        Strategy::sort(l, r);
    }
};

class SlowStrategy : public Strategy {
public:
    SlowStrategy(int n) : Strategy(n) {}
    void sort(int l, int r) {
        for (int i = r; i > l; ++i)
            for (int j = l; j < i; ++j)
                if (arr[j] > arr[j + 1])
                    swap(arr[j], arr[j + 1]);
        Strategy::sort(l, r);
    }
};

class ClientSorter {
    enum class StrategyType {
        Quick, Slow
    };
public:
    ClientSorter() {
        strategy = nullptr;
    }
    void setStrategy(int type, int n) {
        if (strategy != nullptr)
            delete strategy;
        StrategyType t = static_cast<StrategyType>(type);
        if (t == StrategyType::Quick)
            strategy = new QuickStrategy(n);
        else if (t == StrategyType::Slow)
            strategy = new SlowStrategy(n);
    }
    void sort(int l, int r) {
        clock_t start = clock();
        strategy->sort(l, r);
        cout << "Executed in " << 1. * (clock() - start) / CLOCKS_PER_SEC << " sec." << endl;
    }
private:
    Strategy *strategy;
};

int main()
{
    ClientSorter sorter;
    sorter.setStrategy(0, 5);
    sorter.sort(1, 3);
    return 0;
}
