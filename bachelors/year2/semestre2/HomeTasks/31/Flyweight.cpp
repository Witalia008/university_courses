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

class Icon {
public:
    Icon(string filename) : _fname(filename) {
        if (_fname == "go")
            _width = _height = 20;
        else if (_fname == "stop")
            _width = _height = 40;
        else if (_fname == "select")
            _width = _height = 60;
        else if (_fname == "undo")
            _width = _height = 30;
        else
            _width = _height = 50;
    }
    string getName() { return _fname; }
    void draw(int x, int y) {
        cout << "   drawing " << _fname << ": upper left(" << x << ", " << y <<
            ") - lower right (" << x + _width << ", " << y + _height << ")" << endl;
    }
private:
    string _fname;
    int _width;
    int _height;
};

class FlyweightFactory {
    static vector<Icon*> _icons;
public:
    static Icon* getIcon(string filename) {
        for (auto i : _icons) {
            if (i->getName() == filename)
                return i;
        }
        _icons.push_back(new Icon(filename));
        return _icons.back();
    }
    static void reportIcons() {
        cout << "Created flyweights: ";
        for (auto i : _icons)
            cout << " " << i->getName();
        cout << endl;
    }
};

vector<Icon*> FlyweightFactory::_icons;

class DialogBox {
protected:
    vector<Icon*> _icons;
    int _iconPanelX;
    int _iconPanelY;
    int _iconsXinc;
public:
    DialogBox(int x, int y, int incr)
        :_iconPanelX(x), _iconPanelY(y), _iconsXinc(incr) {}
    virtual void draw() = 0;
};

void DialogBox::draw() {
    for (int i = 0; i < _icons.size(); ++i)
        _icons[i]->draw(i * _iconsXinc + _iconPanelX, _iconPanelY);
}

class FileSelection : public DialogBox {
public:
    FileSelection(initializer_list<Icon*> lst) : DialogBox(100, 100, 100) { _icons = lst; }
    void draw() override {
        cout << "Drawing File Selection Dialog Box:" << endl;
        DialogBox::draw();
    }
};

class CommitTransaction : public DialogBox {
public:
    CommitTransaction(initializer_list<Icon*> lst) : DialogBox(150, 150, 150) { _icons = lst; }
    void draw() override {
        cout << "Drawing File Selection Dialog Box:" << endl;
        DialogBox::draw();
    }
};

#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    DialogBox* dialogs[2] = {
        new FileSelection({
            FlyweightFactory::getIcon("go"),
            FlyweightFactory::getIcon("cancel"),
            FlyweightFactory::getIcon("select"),
            FlyweightFactory::getIcon("undo")
        }),
        new CommitTransaction({
            FlyweightFactory::getIcon("go"),
            FlyweightFactory::getIcon("stop"),
            FlyweightFactory::getIcon("undo")
        })
    };
    for (int i = 0; i < 2; ++i)
        dialogs[i]->draw();
    FlyweightFactory::reportIcons();
    system("pause");
    return 0;
}