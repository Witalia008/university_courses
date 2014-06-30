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

class State;

class Car {
private:
    State *current;
public:
    Car();
    void setState(State *_new) {
        current = _new;
    }
    void accelerate();
};

class State {
public:
    virtual void accelerate(Car *car);
};

class SpaceSpeed : public State {
};

class HighSpeed : public State {
public:
    void accelerate(Car *car) override {
        car->setState(new SpaceSpeed());
        cout << "You've got first space speed and left bounds of this planet!" << endl;
    }
};

class MediumSpeed : public State {
public:
    void accelerate(Car *car) override {
        car->setState(new HighSpeed());
        cout << "Running on medium speed." << endl;
    }
};

class LowSpeed : public State {
public:
    void accelerate(Car *car) override {
        car->setState(new MediumSpeed());
        cout << "Running on medium speed" << endl;
    }
};

class Off : public State {
public:
    void accelerate(Car *car) override {
        car->setState(new LowSpeed());
        cout << "Running on low speed" << endl;
    }
};

void State::accelerate(Car *car) {
    car->setState(new Off());
    cout << "Turned off" << endl;
}

Car::Car() {
    current = new Off();
}

void Car::accelerate() {
    current->accelerate(this);
}

#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    Car car;
    for (int i = 0; i < 4; ++i)
        car.accelerate();
    return 0;
}
