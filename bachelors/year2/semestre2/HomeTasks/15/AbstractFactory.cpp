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

class Dish {
public:
    Dish() {
        id = total++;
    }
    virtual void serve() = 0;
protected:
    int id;
    static int total;
};

int Dish::total = 0;

class IceCreamSandwich : public Dish {
public:
    void serve() {
        cout << "4.0.3 - 4.0.4| You're eating ice cream sandwich #" << id << endl;
    }
};

class KitKat : public Dish {
public:
    void serve() {
        cout << "4.4| You're eating KitKat #" << id << endl;
    }
};

class JellyBean : public Dish {
public:
    void serve() {
        cout << "4.1.x - 4.3| You're eating JellyBean #" << id << endl;
    }
};

class HoneyComb : public Dish {
public:
    void serve() {
        cout << "3.2| You're eating HoneyComb #" << id << endl;
    }
};

class Factory {
public:
    virtual Dish* createEntree() = 0;
    virtual Dish* createDesert() = 0;
};

class OldFactory : public Factory {
public:
    Dish* createEntree() {
        return new IceCreamSandwich();
    }
    Dish* createDesert() {
        return new HoneyComb();
    }
};

class ModernFactory : public Factory {
public:
    Dish* createEntree() {
        return new JellyBean();
    }
    Dish* createDesert() {
        return new KitKat();
    }
};

int main()
{
    Factory* factory = new OldFactory();
    vector<Dish*> dishes;
    dishes.push_back(factory->createDesert());
    dishes.push_back(factory->createEntree());
    dishes.push_back(factory->createDesert());
    for (Dish* i: dishes)
        i->serve();
    return 0;
}
