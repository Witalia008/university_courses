#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include <iterator>
#include <cctype>

using namespace std;

class Component {
public:
    virtual double calc() = 0;
};

class Composite : Component {
    string name;
    vector<Component*> sons;
public:
    Composite(string _name) {
        name = _name;
    }
    double calc();
    void Add(Component* _new) {
        sons.push_back(_new);
    }
    void Remove(Component* _toDel) {
        vector<Component*>::iterator it = find(sons.begin(), sons.end(), _toDel);
        if (it != sons.end())
            sons.erase(it);
    }
    Component* getChild(int num) {
        if (num >= 0 && num <= sons.size())
            return sons[num];
        return nullptr;
    }
};

class Leaf : Component {
    double num;
public:
    Leaf(double value) {
        num = value;
    }
    double calc() {
        return num;
    }
};

double Composite::calc() {
    Component* son_0 = this->getChild(0);
    if (son_0 == nullptr)
        return numeric_limits<double>::quiet_NaN();
    double res = son_0->calc();

    if (name == "+")
        res += sons[1]->calc();
    else if (name == "-")
        res -= sons[1]->calc();
    else if (name == "/") {
        double b = sons[1]->calc();
        if (b == 0)
            res = numeric_limits<double>::infinity();
        else
            res /= sons[1]->calc();
    } else if (name == "*")
        res *= sons[1]->calc();
    else if (name == "^")
        res = pow(res, sons[1]->calc());
    return res;
}

class Client {
    string expr;
    int pos;
    Component *root;
    static const vector<string> opers;

    Component* expression(int depth) {
        if (depth >= opers.size())
            return operand();
        Component* res = expression(depth + 1);
        while (pos < expr.size() && opers[depth].find(expr[pos]) != -1) {
            Composite* cur = new Composite(expr.substr(pos++, 1));
            cur->Add(res);
            cur->Add(expression(depth + 1));
            res = (Component*)cur;
        }
        return res;
    }
    Component* operand() {
        if (pos >= expr.size())
            return nullptr;
        if (expr[pos] == '(') {
            Component* res = (++pos, expression(0));
            return (++pos, res);
        }
        return read_num();
    }
    Component* read_num() {
        string res = "";
        if (pos < expr.size() && (expr[pos] == '-' || expr[pos] == '+'))
            res += expr[pos++];
        while (pos < expr.size() && isdigit(expr[pos]))
            res += expr[pos++];
        if (pos < expr.size()) {
            if (expr[pos] == '.') {
                do {
                    res += expr[pos++];
                } while (pos < expr.size() && isdigit(expr[pos]));
            } else if (expr[pos] == 'E' || expr[pos] == 'e') {
                res += expr[pos++];
                if (pos < expr.size() && (expr[pos] == '-' || expr[pos] == '+'))
                    res += expr[pos++];
                while (pos < expr.size() && isdigit(expr[pos]))
                    res += expr[pos++];
            }
        }
        double numb;
        sscanf(res.c_str(), "%lf", &numb);
        return (Component*)(new Leaf(numb));
    }
public:
    Client(string s) {
        expr = s;
        pos = 0;
        root = expression(0);
    }
    double evaluate() {
        return root->calc();
    }
};

const vector<string> Client::opers = {"+-", "*/", "^"};

int main()
{
    Client clc("2+2.5-1/0");
    cout << clc.evaluate() << endl;
    return 0;
}
