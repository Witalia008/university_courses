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

class Ship {
    int _width, _height;
    int _x, _y;
    int _dead;
public:
    Ship(int w, int h) {
        _width = w;
        _height = h;
    }
    int getWidth() const {
        return _width;
    }
    int getHeight() const {
        return _height;
    }
    void set(int x, int y) {
        _x = x; _y = y;
    }
    bool in(int x, int y) {
        return x >= _x && y >= _y && x < _x + _height && y < _y + _width;
    }
    void shoot(int x, int y) {
        if (in(x, y))
            ++_dead;
    }
    bool isAlive() {
        return _dead != _width * _height;
    }
    int X() const {
        return _x;
    }
    int Y() const {
        return _y;
    }
};

class Field {
protected:
    enum class CellType {EMPTY, SHIP, DESTROYED, SHOT};
    vector<vector<CellType>> _field;
    vector<pair<int, Ship>> _ships_data;
    vector<Ship> _ships;
    static string _patt;
    int width, height;
    bool _started;
    bool _finished;
    Field* _rival;
public:
    Field() {
        width = height = _patt.size();
        _field.resize(height);
        for (auto &i : _field)
            i.assign(width, CellType::EMPTY);
        _ships_data = { make_pair(1, Ship(4, 1)), make_pair(2, Ship(3, 1)), make_pair(3, Ship(2, 1)), make_pair(4, Ship(1, 1)) };
        _started = _finished = false;
        _rival = nullptr;
    }
    int getIdx(char x) {
        for (int i = 0; i < height; ++i) {
            if (_patt[i] == x)
                return i;
        }
        return -1;
    }
    CellType getCell(char x, int y) {
        int i = getIdx(x);
        if (i == -1)
            return CellType::EMPTY;
        return _field[i][y];
    }
    void setCell(int x, int y, CellType tp) {
        int i = getIdx(x);
        if (i == -1)
            return;
        _field[i][y] = tp;
    }
    Ship getShip(char x, int y) {
        if (getCell(x, y) != CellType::DESTROYED && getCell(x, y) != CellType::SHIP)
            return Ship(-1, -1);
        for (auto &i : _ships) {
            if (i.in(x, y))
                return i;
        }
    }
    bool canPutShip(char x, int y, Ship c) {
        x = getIdx(x);
        for (int i = x - 1; i <= x + c.getWidth(); ++i) {
            for (int j = y - 1; j <= y + c.getHeight(); ++j) {
                if (i >= 0 && j >= 0 && i < width && j < height && _field[i][j] != CellType::EMPTY)
                    return false;
            }
        }
        return true;
    }
    void putShip(Ship c) {
        for (int i = c.X(); i < c.X() + c.getWidth(); ++i) {
            for (int j = c.Y(); j < c.Y() + c.getHeight(); ++j) {
                if (i >= 0 && j >= 0 && i < width && j < height)
                    _field[i][j] = CellType::SHIP;
            }
        }
    }
    bool isEnd() {
        for (auto &i : _ships) {
            if (i.isAlive())
                return false;
        }
        return true;
    }
    string getCh(CellType c) const {
        if (c == CellType::EMPTY)
            return ".";
        if (c == CellType::SHOT)
            return "-";
        if (c == CellType::SHIP)
            return "o";
        if (c == CellType::DESTROYED)
            return "x";
    }
    virtual void doStep(char, int) = 0;
    virtual void startGame(Field*, bool) = 0;
    virtual void nextStep() = 0;
    virtual void putShips() = 0;
};

string Field::_patt = "RESPUBLICA";

void Field::doStep(char x, int y) {
    Ship i = getShip(x, y);
    if (i.getWidth() != -1)
        i.shoot(getIdx(x), y);
    setCell(x, y, getCell(x, y) == CellType::EMPTY ? CellType::SHOT : CellType::DESTROYED);
}

void Field::startGame(Field *other, bool conn) {
    if (other == nullptr)
        return;
    _started = true;
    _rival = other;
    if (conn) {
        other->startGame(this, false);
    }
    putShips();
}

class UserField : public Field {
public:
    UserField() : Field() {}
    void startGame(Field *other, bool conn) override {
        Field::startGame(other, conn);
    }
    void nextStep() override {
        if (!_started)
            return;
        char x;
        int y;
        do {
            cout << "Enter cell coords: ";
            cin >> x >> y;
        } while (_patt.find(x) == -1 || getCell(x, y) != CellType::EMPTY && getCell(x, y) != CellType::SHIP);
        doStep(x, y);
    }
    void doStep(char x, int y) override {
        Field::doStep(x, y);
        if (getCell(x, y) == CellType::SHOT)
            cout << "You've missed!" << endl;
        else {
            cout << "You've got it!" << endl;
            if (!getShip(x, y).isAlive())
                cout << "Ship is dead!" << endl;
        }
        if (!isEnd())
            _rival->nextStep();
        else
            cout << "You won!" << endl;
    }
    void putShips() override {
        cout << "Put your ships" << endl;
        for (auto &i : _ships_data) {
            for (int j = 0; j < i.first; ++j) {
                outputField();
                int w = i.second.getWidth(), h = i.second.getHeight();
                cout << "Ship " << w << "x" << h << endl;
                cout << "Orient. 0 - gor, 1 - vert" << endl;
                char x;  int y; cin >> y;
                if (y) swap(w, h);
                Ship cur(w, h);
                do {
                    cout << "Enter position (x, y):";
                    cin >> x >> y;
                } while (_patt.find(x) == -1 || !canPutShip(x, y, cur));
                cur.set(getIdx(x), y);
                _ships.push_back(cur);
                putShip(cur);
            }
        }
    }
    void outputField() const {
        cout << "  " << _patt << "   " << _patt << endl;
        for (int i = 0; i < height; ++i) {
            cout << i << " ";
            for (int j = 0; j < width; ++j)
                cout << getCh(_field[j][i]);
            cout << " " << i << " ";
            for (int j = 0; j < width; ++j) {
                string s = getCh(_rival->getCell(_patt[i], j));
                if (s == "o") s = ".";
                cout << s;
            }
            cout << endl;
        }
    }
};

class CompField : public Field {
public:
    CompField() : Field() {}
    void startGame(Field *other, bool conn) override {
        Field::startGame(other, conn);
    }
    void nextStep() override {
        if (!_started)
            return;
        char x;
        int y;
        do {
            x = _patt[rand() % _patt.size()];
            y = rand() % height;
        } while (getCell(x, y) != CellType::EMPTY && getCell(x, y) != CellType::SHIP);
        doStep(x, y);
    }
    void doStep(char x, int y) override {
        Field::doStep(x, y);
        if (!isEnd())
            _rival->nextStep();
        else
            cout << "Computer won!" << endl;
    }
    void putShips() override {
        for (auto &i : _ships_data) {
            for (int j = 0; j < i.first; ++j) {
                int w = i.second.getWidth(), h = i.second.getHeight();
                char x;  int y;
                if (rand() & 1) swap(w, h);
                Ship cur(w, h);
                do {
                    x = _patt[rand() % _patt.size()];
                    y = rand() % height;
                } while (_patt.find(x) == -1 || !canPutShip(x, y, cur));
                cur.set(x, y);
                _ships.push_back(cur);
            }
        }
    }
};

#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    Field* pl1 = new UserField();
    Field* pl2 = new CompField();
    pl1->startGame(pl2, true);
    pl1->nextStep();
    system("pause");
    return 0;
}