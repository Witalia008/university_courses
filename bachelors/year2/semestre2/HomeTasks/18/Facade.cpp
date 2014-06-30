#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <iterator>

using namespace std;

class Tank {
    double amount;
    double size;
public:
    Tank(double sz) : size(sz), amount(0) {}
    bool isEmpty() {
        return amount == 0;
    }
    void fill(double am) {
        amount = min(amount + am, size);
    }
    bool get(double am) {
        if (amount >= am) {
            amount -= am;
            return true;
        }
        return false;
    }
};

class Engine {
    bool is_running;
public:
    Engine() : is_running(false) {}
    bool getFuel(Tank &a) {
        return a.get(.1);
    }
    void run() {
        is_running = true;
    }
};

class Vehicle {
    Tank *tank;
    Engine *engine;
public:
    Vehicle() {
        tank = new Tank(40);
        engine = new Engine();
    }
    ~Vehicle() {
        delete tank;
        delete engine;
    }
    void fillTank(double am) {
        tank->fill(am);
    }
    bool start() {
        if (tank->isEmpty())
            return false;
        tank->get(.1);
        engine->run();
        return true;
    }
};

int main()
{
    Vehicle car;
    car.fillTank(20);
    cout << car.start() << endl;
    return 0;
}
