#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <Windows.h>
#include <initializer_list>
#include <iomanip>

using namespace std;

class Matrix {
    int _n, _m;
    vector<vector<double>> _data;
public:
    Matrix(int n, int m)
        :_n(n), _m(m)
    {
        _data = vector<vector<double>>(n, vector<double>(m, 0));
    }
    Matrix(int n, bool one = false)
        : Matrix(n, n){
        if (one) {
            for (int i = 0; i < n; ++i)
                _data[i][i] = 1;
        }
    }
    Matrix(initializer_list<vector<double>> lst)
        :_data(lst)
    {
        _n = _data.size();
        if (_n) _m = _data[0].size();
        else _m = 0;
    }
    double S() {
        double res = 0;
        for (int i = 0; i < _n; ++i) {
            for (int j = 0; j < _m; ++j) {
                if (i != j)
                    res += _data[i][j] * _data[i][j];
            }
        }
        return res;
    }
    double get(int i, int j) const {
        if (i < 0 || i >= _n || j < 0 || j >= _m)
            return 0;
        return _data[i][j];
    }
    void set(int i, int j, double val) {
        if (i < 0 || i >= _n || j < 0 || j >= _m)
            return;
        _data[i][j] = val;
    }
    bool symm() {
        if (_n != _m)
            return false;
        for (int i = 0; i < _n; ++i) {
            for (int j = i + 1; j < _m; ++j) {
                if (_data[i][j] != _data[j][i])
                    return false;
            }
        }
        return true;
    }
    pair<int, int> getMax() {
        pair<int, int> res(0, 1);
        for (int i = 0; i < _n; ++i) {
            for (int j = i + 1; j < _m; ++j) {
                if (fabs(_data[i][j]) > fabs(_data[res.first][res.second]))
                    res = { i, j };
            }
        }
        return res;
    }
    Matrix operator * (const Matrix& b) {
        if (_m != b._n)
            return Matrix(0);
        Matrix res(_n, b._m);
        for (int i = 0; i < res._n; ++i) {
            for (int j = 0; j < res._m; ++j) {
                res._data[i][j] = 0;
                for (int k = 0; k < _m; ++k)
                    res._data[i][j] += _data[i][k] * b._data[k][j];
            }
        }
        return res;
    }
    Matrix transp() {
        Matrix res(_m, _n);
        for (int i = 0; i < _n; ++i) {
            for (int j = 0; j < _m; ++j)
                res._data[j][i] = _data[i][j];
        }
        return res;
    }
    int N() const { return _n; };
    int M() const { return _m; }
};

ostream &operator << (ostream &out, const Matrix& a) {
    out << a.N() << "x" << a.M() << endl;
    for (int i = 0; i < a.N(); ++i) {
        for (int j = 0; j < a.M(); ++j) {
            cout << a.get(i, j) << " ";
        }
        cout << endl;
    }
    return out;
}

const double eps = 1e-7;

Matrix jakobi(Matrix &A) {
    Matrix res(A.N(), true);
    if (A.N() < 2)
        return res;
    while (A.S() > eps) {
        auto pos = A.getMax();

        double phi = atan(2 * A.get(pos.first, pos.second) / (A.get(pos.first, pos.first) - A.get(pos.second, pos.second))) / 2;

        Matrix Ui(A.N(), true);
        Ui.set(pos.first, pos.first, cos(phi));
        Ui.set(pos.second, pos.second, cos(phi));
        Ui.set(pos.first, pos.second, -sin(phi));
        Ui.set(pos.second, pos.first, sin(phi));

        res = res * Ui;
        A = Ui.transp() * A * Ui;
    }
    return res;
}

void eigenvalues(Matrix A) {
    cout << "Jakobi rotation method\n";
    if (A.symm() == false) {
        cout << "Must be symmetric!\n";
        return;
    }
    cout << "Matrix A:\n";
    cout << A << endl;
    Matrix U = jakobi(A);
    cout << "Eigenvalues:\n";
    for (int i = 0; i < A.N(); ++i)
        cout << A.get(i, i) << endl;
    cout << endl;
    cout << "Eigenvectors (columns corresponding to eigenvalue):\n";
    cout << U << endl;
}

int main() {
    //freopen("output.txt", "w", stdout);
    cout << fixed << setprecision(3);

    Matrix A = {
        { 2.2,   1, 0.5,   2 },
        {   1, 1.3,   2,   1 },
        { 0.5,   2, 0.5, 1.6 },
        {   2,   1, 1.6,   2 }
    };

    eigenvalues(A);

    system("pause");
    return 0;
}
