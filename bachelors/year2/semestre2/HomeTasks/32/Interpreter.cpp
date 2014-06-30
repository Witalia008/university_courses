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
#include <initializer_list>


using namespace std;
using namespace std::chrono;

typedef long long ll;

const int N = 100005;
const int K = 505;
const ll InfL = 1000000000000000000LL;
const int MOD = 1000000007;

class Expression {
public:
    virtual double interpret() = 0;
};

class Number : public Expression {
    double _value;
public:
    Number(double num) : _value(num) {}
    double interpret() override {
        return _value;
    }
};

class BinExpr : public Expression {
protected:
    Expression *_left, *_right;
    BinExpr(Expression *left, Expression *right) : _left(left), _right(right) {}
public:
    virtual double interpret() = 0;
};

class MulExpr : public BinExpr {
public:
    MulExpr(Expression *left, Expression *right) : BinExpr(left, right) {}
    double interpret() override {
        return _left->interpret() * _right->interpret();
    }
};

class DivExpr : public BinExpr {
public:
    DivExpr(Expression *left, Expression *right) : BinExpr(left, right) {}
    double interpret() override {
        double r = _right->interpret();
        if (r == 0)
            return numeric_limits<double>::quiet_NaN();
        return _left->interpret() / r;
    }
};

class AddExpr : public BinExpr {
public:
    AddExpr(Expression *left, Expression *right) : BinExpr(left, right) {}
    double interpret() override {
        return _left->interpret() + _right->interpret();
    }
};

class SubExpr : public BinExpr {
public:
    SubExpr(Expression *left, Expression *right) : BinExpr(left, right) {}
    double interpret() override {
        return _left->interpret() - _right->interpret();
    }
};

int pos = 0;
Expression* parse(string s, int type) {
    if (pos >= s.size())
        return new Number(0);
    if (type < 2) {
        Expression *left = parse(s, type + 1);
        static const string opers[2] = { "+-", "*/" };
        while (pos < s.size() && opers[type].find(s[pos]) != -1) {
            char c = s[pos++];
            Expression* right = parse(s, type + 1);
            if (c == '-') left = new SubExpr(left, right); else
            if (c == '+') left = new AddExpr(left, right); else
            if (c == '/') left = new DivExpr(left, right); else
                left = new MulExpr(left, right);
        }
        return left;
    }
    else if (type == 2) {
        if (s[pos] == '(') {
            ++pos;
            Expression* res = parse(s, 0);
            return (++pos, res);
        }
        return parse(s, type + 1);
    }
    else {
        double x;
        sscanf(s.c_str() + pos, "%lf", &x);
        while (pos < s.size() && isdigit(s[pos])) ++pos;
        if (pos < s.size() && s[pos] == '.') ++pos;
        while (pos < s.size() && isdigit(s[pos])) ++pos;
        return new Number(x);
    }
}

#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    string s;
    cin >> s;
    Expression* interpreter = parse(s, 0);
    cout << interpreter->interpret() << endl;
    system("pause");
    return 0;
}