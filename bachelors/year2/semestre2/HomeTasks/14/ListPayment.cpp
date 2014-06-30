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

class Person {
protected:
    int _number;
    string _name, _fname, _surname;
    double _salary;
    int _startYear;
    double _percent;
    double _incomeTax;
    int _daysWorked;
    int _workDays;
    double _income;
    double _takes;
public:
    virtual int experience(int curYear) {
        return max(curYear - _startYear, 0);
    }
    virtual double getIncome() {
        return _daysWorked * _income / _workDays * (1 + _percent / 100);
    }
    virtual double takes() {
        return retireTax() + incomeTax();
    }
    virtual double incomeTax() {
        return getIncome() * 0.13;
    }
    virtual double retireTax() {
        return getIncome() * 0.01;
    }
    virtual bool operator == (Person other) {
        if (other._number >= 0 && other._number != _number)
            return false;
        if (other._name != "" && other._name != _name)
            return false;
        if (other._surname != "" && other._surname != _surname)
            return false;
        if (other._fname != "" && other._fname != _fname)
            return false;
        if (other._salary >= 0 && other._salary != _salary)
            return false;
        if (other._startYear >= 0 && other._startYear != _startYear)
            return false;
        if (other._percent >= 0 && other._percent != _percent)
            return false;
        if (other._incomeTax >= 0 && other._incomeTax != _incomeTax)
            return false;
        if (other._daysWorked >= 0 && other._daysWorked != _daysWorked)
            return false;
        if (other._workDays >= 0 && other._workDays != _workDays)
            return false;
        if (other._income >= 0 && other._income != _income)
            return false;
        if (other._takes >= 0 && other._takes != _takes)
            return false;
        return true;
    }
};

class Group {
    vector<Person*> persons;
public:
    void add(Person *nWorker) {
        persons.push_back(nWorker);
    }
    int experience(int curYear) {
        return persons.size() ? persons.back()->experience(curYear) : -1;
    }
};

class ListPayment {
protected:
    vector<Person*> persons;
public:
    void add(Person *nWorker) {
        persons.push_back(nWorker);
    }
    void remove(Person *worker) {
        vector<Person*>::iterator it;
        if ((it = std::find(persons.begin(), persons.end(), worker)) != persons.end())
            persons.erase(it);
    }
    void merge(const ListPayment& other) {
        persons.insert(persons.end(), other.persons.begin(), other.persons.end());
    }
    vector<Person*> find(Person *patt) {
        vector<Person*> res;
        for (auto i : persons) {
            if (*i == *patt)
                res.push_back(i);
        }
        return res;
    }
    double overall(double (Person::*func)()) {
        double res = 0;
        for (auto i : persons)
            res += (i->*func)();
        return res;
    }
    vector<Group> group(int curYear) {
        vector<Group> res;
        for (auto i : persons) {
            int idx = res.size();
            for (int j = 0; j < res.size(); ++j) {
                if (res[j].experience(curYear) == i->experience(curYear))
                    idx = j;
            }
            if (idx == res.size())
                res.push_back(Group());
            res[idx].add(i);
        }
        return res;
    }
};

#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    return 0;
}