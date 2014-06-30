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

class Person {
protected:
    string _name;
public:
    Person(string name) : _name(name) {}
    string getName() { return _name; }
    virtual ~Person() {}
};

class Account {
    friend class Client;
    friend class Admin;
    friend class Bank;
protected:
    double _amount;
    double _creditLim;
    double _credit;
    bool _blocked;
    Account(double cl) : _amount(0), _creditLim(cl), _credit(0), _blocked(false) {}
public:
    void load(double am) {
        if (_blocked) return;
        _credit -= am;
        if (_credit < 0) {
            _amount -= _credit;
            _credit = 0;
        }
    }
    void get(double am) {
        if (_blocked) return;
        _amount -= am;
        if (_amount < 0) {
            _credit -= _amount;
            _amount = 0;
        }
    }
    virtual ~Account() {}
};

class Order {
protected:
    double _price;
public:
    Order(double p) : _price(p) {}
    double getPrice() { return _price; }
};

class CreditCard {
    friend class Bank;
protected:
    Account *acc;
    CreditCard(Account* a) : acc(a) {}
public:
    void withdraw(double am) {
        acc->get(am);
    }
    virtual ~CreditCard() {}
};

class Admin : public Person {
public:
    void blockIfOverflow(Account *acc) {
        if (acc != nullptr && acc->_credit > acc->_creditLim)
            acc->_blocked = true;
    }
};

class Client : public Person {
    friend class Bank;
protected:
    Account *acc;
    vector<CreditCard*> cards;
public:
    Client(string name) : Person(name), acc(nullptr) {}
    void pay(Order *ord) {
        acc->get(ord->getPrice());
    }
    void pay(Account *other, double am) {
        acc->get(am);
        other->load(am);
    }
    void block() {
        acc->_blocked = true;
    }
    void annulate() {
        for (auto &i : cards) 
            if (i != nullptr) {
                delete i;
                i = nullptr;
            }
        cards.clear();
    }
    virtual ~Client() {
        annulate();
    }
};

class Bank {
protected:
    vector<Account*> _accs;
public:
    void createAccount(Client *p) {
        if (p->acc != nullptr) return;
        p->acc = new Account(100);
        _accs.push_back(p->acc);
    }
    void getCreditCard(Client *p) {
        if (p->acc == nullptr) return;
        p->cards.push_back(new CreditCard(p->acc));
    }
    virtual ~Bank() {
        for (auto &i : _accs) 
            if (i != nullptr) {
                delete i;
                i = nullptr;
            }
    }
};

#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    Client *cl = new Client("Adam");
    Bank ccl;
    ccl.createAccount(cl);
    ccl.getCreditCard(cl);
    cl->pay(new Order(50));
    return 0;
}