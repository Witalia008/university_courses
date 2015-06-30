#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <Windows.h>
#include <initializer_list>
#include <iomanip>

using namespace std;

double step = 0.01;

class Interpol {
    double (*_func)(double);
    int _n;
    bool _inv;
    vector<pair<double, double>> _nodes;
    vector<vector<double>> _fdiff;
    double _a, _b;
    void genNodes(int n) {
        _nodes.resize(_n = n + 1);
        for (int i = 0; i <= n; ++i) {
            _nodes[i].first = _a + i * (_b - _a) / n;
            _nodes[i].second = _func(_nodes[i].first);
            if (_inv)
                swap(_nodes[i].first, _nodes[i].second);
        }
    }
    void calcFDiff() {
        if (_nodes.size() != _n)
            return;
        _fdiff.resize(_n);
        for (int i = 0; i < _n; ++i) {
            _fdiff[i].clear();
            _fdiff[i].push_back(_nodes[i].second);
        }
        for (int j = 1; j < _n; ++j) {
            for (int i = 0; i < _n - j; ++i) {
                _fdiff[i].push_back((_fdiff[i + 1][j - 1] - _fdiff[i][j - 1]) / (_nodes[i + j].first - _nodes[i].first));
            }
        }
        cout << "Show?: ";
        char q; cin >> q;
        if (q == 'y') {
            cout << "Divided difference:\n";
            for (int i = 0; i < _n; ++i) {
                cout << _nodes[i].first << " ";
                for (double j : _fdiff[i])
                    cout << j << " ";
                cout << endl;
            }
        }
    }
public:
    Interpol(double f(double), double a, double b, bool inv)
        : _func(f), _inv(inv), _a(a), _b(b)
    {
        if (a > b) swap(a, b);
        cout << "Enter number of nodes: ";
        int n; cin >> n;
        genNodes(n);
        calcFDiff();
    }
    double get(double x) {
        double res = _fdiff[0].back();
        for (int i = _n - 1; i > 0; --i) {
            res = res * (x - _nodes[i - 1].first) + _fdiff[0][i - 1];
        }
        return res;
    }
    void output() {
        cout << "Ln(x) = \n";
        for (int j = 0; j < _n; ++j) {
            cout << _fdiff[0][j];
            for (int i = 0; i < j; ++i)
                cout << " * (x - " << _nodes[i].first << ")";
            if (j != _n - 1) cout << " +";
            cout << endl;
        }
    }
    bool isInv() { return _inv; }
};

auto F = [](double x) {
    return 5 * x + x * x * sin(x);
};

void drawPlot(double a, double b, Interpol &p) {
    system("cls");
    int width = 200, height = 600;
    double coef = .5 * height * (b - a) / width;

    HDC hDC = GetDC(GetConsoleWindow());
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    SelectObject(hDC, pen);
    MoveToEx(hDC, 0, height / 2, 0);
    LineTo(hDC, width, height / 2);
    if (a < 0 && b > 0) {
        MoveToEx(hDC, (-a / (b - a)) * width, 0, 0);
        LineTo(hDC, (-a / (b - a)) * width, height);
    }
    for (double i = a; i < b; i += step) {
        MoveToEx(hDC, width * (i - a) / (b - a), (1 - F(i) / coef) * height / 2, 0);
        double y1 = F(i), y2 = p.get(i);
        if (!p.isInv())
            LineTo(hDC, width * (i - a) / (b - a), (1 - p.get(i) / coef) * height / 2 - 1);
        else
            LineTo(hDC, width * (p.get(F(i)) - a) / (b - a) - 1, (1 - F(i) / coef) * height / 2);
    }
}

int main() {
    //freopen("output.txt", "w", stdout);
    cout << fixed << setprecision(3);

    cout << "Enter interval [a; b]: ";
    double a, b; cin >> a >> b;
    Interpol P(F, a, b, false);
    //P.output();
    drawPlot(a, b, P);
    cout << "Enter some x-value: ";
    double y; cin >> y;
    cout << "P(" << y << ") = " << P.get(y) << endl;
    cout << "F(" << y << ") = " << F(y) << endl;

    system("pause");

    cout << "Enter interval [a; b]: ";
    cin >> a >> b;
    Interpol Q(F, a, b, true);
    Q.output();
    //drawPlot(a, b, Q);
    cout << "Enter some y-value: ";
    cin >> y;
    cout << "F(" << Q.get(y) << ") = " << y << endl;

    system("pause");
    return 0;
}
