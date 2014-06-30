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

class Memento {
    string _state;
public:
    Memento(string st) {
        _state = st;
    }
    string getSavedState() {
        return _state;
    }
};

class Originator {
    string _state;
public:
    Originator() {
        set("N/A");
    }
    Originator(string state) {
        set(state);
    }
    void set(string state) {
        cout << "Originator: setting state to " << state << endl;
        _state = state;
    }
    Memento* saveToMemento() {
        cout << "Originator: saving to Memento" << endl;
        return new Memento(_state);
    }
    void restoreFromMemento(Memento *mem) {
        _state = mem->getSavedState();
        cout << "Originator: state after restoring from Memento: " << _state << endl;
    }
};

class Caretaker {
    vector<Memento*> savedStates;
public:
    void addMemento(Memento *mem) {
        savedStates.push_back(mem);
    }
    Memento* getMemento(int index) {
        if (index < 0 || index >= savedStates.size())
            return nullptr;
        return savedStates[index];
    }
};

#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    Caretaker caretaker;
    Originator originator;
    caretaker.addMemento(originator.saveToMemento());
    originator.set("State 0");
    caretaker.addMemento(originator.saveToMemento());
    originator.set("State 1");
    originator.set("State 2");
    originator.restoreFromMemento(caretaker.getMemento(1));
    originator.set("State 3");
    caretaker.addMemento(originator.saveToMemento());
    system("pause");
    return 0;
}