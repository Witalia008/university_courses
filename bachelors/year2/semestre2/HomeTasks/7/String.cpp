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

string toString(int a) {
    char s[100] = {};
    sprintf(s, "%d", a);
    return string(s);
}

class SymbString {
protected:
    string _id;
    static int _total;
    string _data;
public:
    SymbString() {
        _id = toString(_total++);
        _data = "";
    }
    SymbString(string s)
        : _data(s) {}
    SymbString(const char *s)
        : SymbString(string(s)) {}
    virtual void show() const {
        cout << "String: " << _data << endl;
    }
    virtual ~SymbString() {}
};

int SymbString::_total = 0;

class NotValidOctStringError : public exception {
public:
    virtual const char* what() const override {
        return "This is not valid octal string";
    }
};

class OctString : public SymbString {
public:
    OctString() : SymbString() {}
    OctString(const char *s) throw(NotValidOctStringError)
        : SymbString(s) 
    {
        if (!isValid(s))
            throw NotValidOctStringError();
    }
    OctString(string s) throw(NotValidOctStringError)
        : SymbString(s)
    {
        if (!isValid(s))
            throw NotValidOctStringError();
    }
    virtual void show() const override {
        cout << "Octal string: " << _data << endl;
    }
    static bool isValid(string s) {
        for (char i : s) {
            if (!isdigit(i) || i == '8' || i == '9')
                return false;
        }
        return true;
    }
};

class Factory {
public:
    virtual SymbString *createSymbString(string s) = 0;
    virtual SymbString *createOctString(string s) = 0;
};

class ConcreteFactory : public Factory {
public:
    virtual SymbString *createSymbString(string s) override {
        return new SymbString(s);
    }
    virtual SymbString *createOctString(string s) override {
        if (!OctString::isValid(s)) {
            return new OctString();
        }
        return new OctString(s);
    }
};

#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    Factory *factory = new ConcreteFactory();
    SymbString *strs[2] = { factory->createSymbString("Hello, world!"), factory->createOctString("010207") };
    for (auto i : strs)
        i->show();
    system("pause");
    return 0;
}