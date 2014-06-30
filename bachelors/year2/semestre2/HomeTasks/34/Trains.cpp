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
#include <tuple>

using namespace std;
using namespace std::chrono;

typedef long long ll;

const int N = 16005;
const int K = 605;
const int Inf = 1000000000;
const ll InfL = 1000000000000000000LL;
const int MOD = 1000000007;

class Station {
protected:
    int _x, _y;
    vector<Station*> _adj;
    vector<class Train*> trains;
    string _name;
public:
    Station(string name, int x, int y) : _name(name), _x(x), _y(y) {}
    void add(Station *other) {
        _adj.push_back(other);
    }
    void addTrain(Train *tr) {
        trains.push_back(tr);
    }
    int getDist(Station *other) {
        auto sqr = [](int a) -> double { return a * a; };
        return int(sqrt(sqr(other->_x - _x) + sqr(other->_y - _y)));
    }
    bool isConnected(Station *other) {
        return find(_adj.begin(), _adj.end(), other) != _adj.end();
    }
    vector<Train*> getTrains(Station *fr, Station *to);
    int getTicket(Station *other);
};

class Car {
protected:
    int _num;
public:
    Car(int num) : _num(num) {}
    virtual int getPrice(int dist) = 0;
    int num() { return _num; }
};

class PCar : public Car {
public:
    enum class Type {SITTING, RESERVED, COMPARTMENT};
    enum class Features{NONE, TV, TELEPHONE};
protected:
    int _npl;
    int _price;
    Type _type;
    Features _ftr;
public:
    PCar(int num, int nplaces, int plPrice, Type t, Features feature)
        : Car(num), _npl(nplaces), _price(plPrice), _type(t), _ftr(feature)
    {}
    Type type() { return _type; }
    Features feature() { return _ftr; }
    int getPrice(int dist) override {
        int res = dist * _price;
        if (_type == Type::RESERVED)
            res += 10;
        else if (_type == Type::COMPARTMENT)
            res += 30;
        if (_ftr == Features::TV)
            res += 40;
        else if (_ftr == Features::TELEPHONE)
            res += 30;
        return res;
    }
};

class SCar : public Car {
public:
    enum class Type { NONE, POST, CAFE, RESTAURANT };
protected:
    Type _type;
public:
    SCar(Type t) : Car(0), _type(t) {}
    Type type() { return _type; }
    int getPrice(int dist) { return 0; }
};


class Train {
protected:
    int _num;
    Station *_depart, *_arrive;
    vector<Car*> cars;
public:
    Train(int num, Station *dp, Station *arr)
        :_num(num), _depart(dp), _arrive(arr)
    {
        dp->add(arr);
        arr->add(dp);
        dp->addTrain(this);
        arr->addTrain(this);
    }
    int num() { return _num; }
    void addCar(Car *car) {
        cars.push_back(car);
    }
    bool goes(Station *fr, Station *to) {
        return _depart == fr && _arrive == to;
    }
    bool has(SCar::Type tp) {
        for (auto i : cars) {
            if (((SCar*)i)->type() == tp)
                return true;
        }
        return false;
    }
    vector<Car*> getCars(PCar::Type tp, PCar::Features ft) {
        vector<Car*> res;
        for (auto i : cars) {
            if (((PCar*)i)->type() == tp && ((PCar*)i)->feature() == ft)
                res.push_back(i);
        }
        return res;
    }
};

vector<Train*> Station::getTrains(Station *fr, Station *to) {
    vector<Train*> res;
    for (auto i : trains) {
        if (i->goes(fr, to))
            res.push_back(i);
    }
    return res;
}

int Station::getTicket(Station *other) {
    if (!isConnected(other))
        return -1;
    vector<Train*> tr = getTrains(this, other);
    if (tr.size() == 0) {
        cout << "No available trains\n";
        return 0;
    }
    cout << "Enter type of car you want:\n0. Sitting\n1.Reserved\n2.Compartment\n";
    int type1, type2, type3;
    cin >> type1; type1 = (type1 % 3 + 3) % 3;
    cout << "Enter type of features you want:\n0. None\n1.TV\n2.Telephone\n";
    cin >> type2; type2 = (type2 % 3 + 3) % 3;
    cout << "Enter type of car included you want:\n0.None\n1.Post\n2.Cafe\n3.Restaurant\n";
    cin >> type3; type3 = (type3 % 4 + 4) % 4;
    vector<pair<Train*, vector<Car*>>> options;
    for (auto i : tr) {
        if (!type3 || i->has(static_cast<SCar::Type>(type3))) {
            options.push_back(make_pair(i, i->getCars(
                static_cast<PCar::Type>(type1),
                static_cast<PCar::Features>(type2)
                )));
        }
    }
    int n = 0;
    for (auto &i : options) {
        cout << "Train number " << i.first->num() << ":\n";
        cout << "N\t Car Number\t Price\t\n";
        for (auto j : i.second) {
            cout << ++n << "\t " << j->num() << "\t " << j->getPrice(this->getDist(other)) << "\t\n";
        }
        system("pause");
    }
    cout << "Enter your choice: ";
    cin >> n;
    for (auto &i : options) {
        for (auto j : i.second) {
            --n;
            if (!n)
                return j->getPrice(this->getDist(other));
        }
        system("pause");
    }
    return -1;
}

#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    Station *st[3] = { new Station("A", 0, 0), new Station("B", 10, 0), new Station("C", 0, 10) };
    Train *X = new Train(1, st[0], st[1]);
    Train *Y = new Train(2, st[0], st[2]);
    Train *Z = new Train(12, st[1], st[2]);
    X->addCar(new PCar(0, 54, 10, PCar::Type::SITTING, PCar::Features::NONE));
    X->addCar(new PCar(1, 54, 20, PCar::Type::RESERVED, PCar::Features::TV));
    X->addCar(new PCar(2, 54, 30, PCar::Type::COMPARTMENT, PCar::Features::NONE));
    X->addCar(new SCar(SCar::Type::RESTAURANT));
    Y->addCar(new PCar(0, 54, 10, PCar::Type::SITTING, PCar::Features::NONE));
    Y->addCar(new PCar(1, 54, 20, PCar::Type::RESERVED, PCar::Features::TV));
    Y->addCar(new PCar(2, 54, 30, PCar::Type::COMPARTMENT, PCar::Features::NONE));
    Y->addCar(new SCar(SCar::Type::RESTAURANT));
    Z->addCar(new PCar(0, 54, 10, PCar::Type::SITTING, PCar::Features::NONE));
    Z->addCar(new PCar(1, 54, 20, PCar::Type::RESERVED, PCar::Features::TV));
    Z->addCar(new PCar(2, 54, 30, PCar::Type::COMPARTMENT, PCar::Features::NONE));
    Z->addCar(new SCar(SCar::Type::RESTAURANT));
    cout << "Price: " << st[0]->getTicket(st[1]) << endl;
    system("pause");
    return 0;
}