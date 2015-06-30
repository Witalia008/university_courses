#include <iostream>
#include <algorithm>
#include <vector>
#include <Windows.h>
#include <initializer_list>
#include <iomanip>

using namespace std;

class Matrix {
public:
    vector<vector<double>> _data;
    int _n, _m;
public:
    Matrix(int n, int m)
        : _n(n), _m(m) 
    {
        _data.resize(n);
        for (auto &i : _data)
            i.resize(m, 0);
    }
    Matrix(initializer_list<vector<double>> lst) : _data(lst) {
        _n = _data.size();
        if (_n) _m = _data[0].size();
    }
    Matrix operator * (const Matrix &b) {
        if (_m != b._n)
            return Matrix(0, 0);
        Matrix res(_n, b._m);
        for (int i = 0; i < res._n; ++i) {
            for (int j = 0; j < res._m; ++j) {
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
    double norm() {
        double res = 0;
        for (int j = 0; j < _m; ++j) {
            double cur = 0;
            for (int i = 0; i < _n; ++i)
                cur += fabs(_data[i][j]);
            res = max(res, cur);
        }
        return res;
    }
    Matrix operator + (Matrix b) {
        if (_n != b._n || _m != b._m)
            return Matrix(0, 0);
        Matrix res(_n, _m);
        for (int i = 0; i < _n; ++i) {
            for (int j = 0; j < _m; ++j)
                res._data[i][j] = _data[i][j] + b._data[i][j];
        }
        return res;
    }
    Matrix operator - (Matrix b) {
        for (int i = 0; i < b._n; ++i) {
            for (int j = 0; j < b._m; ++j)
                b._data[i][j] *= -1;
        }
        return *this + b;
    }
    //friend ostream& operator << (ostream &, const Matrix&);
};

ostream& operator << (ostream &out, const Matrix& A) {
    out << A._n << "x" << A._m << endl;
    for (int i = 0; i < A._n; ++i) {
        for (int j = 0; j < A._m; ++j)
            cout << A._data[i][j] << (j != A._m - 1 ? " " : "\n");
    }
    return out;
}

Matrix gilbert(int n) {
    Matrix res(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            res._data[i][j] = 1. / (i + j + 1);
    }
    return res;
}

void substr(Matrix &A, int x, int y, double c) {
    for (int i = 0; i < A._m; ++i)
        A._data[x][i] -= A._data[y][i] * c;
}

void swap(Matrix &A, int i, int j) {
    for (int k = 0; k < A._m; ++k)
        swap(A._data[i][k], A._data[j][k]);
}

void makeTriangle(Matrix &A, bool norm) {
    for (int i = 0; i < A._n; ++i) {
        int mi = i;
        for (int j = i + 1; j < A._n; ++j) {
            if (A._data[j][i] > A._data[mi][i])
                mi = j;
        }
        if (i != mi) swap(A, i, mi);

        if (norm) {
            double coef = 1 / A._data[i][i];
            for (int j = i; j < A._m; ++j)
                A._data[i][j] *= coef;
        }
        for (int j = i + 1; j < A._n; ++j) {
            double coef = A._data[j][i] / A._data[i][i];
            substr(A, j, i, coef);
        }
    }
}

Matrix solveLES(Matrix A, Matrix b) {
    if (b._m != 1 || b._n != A._m || A._n < A._m)
        return Matrix(0, 0);
    for (int i = 0; i < A._n; ++i)
        A._data[i].push_back(b._data[i][0]);
    A._m++;
    makeTriangle(A, true);
    Matrix res(A._n, 1);
    for (int i = A._n - 1; i >= 0; --i) {
        res._data[i][0] = A._data[i][A._m - 1];
        for (int j = i + 1; j < A._n; ++j)
            res._data[i][0] -= res._data[j][0] * A._data[i][j];
        res._data[i][0] /= A._data[i][i];
    }
    return res;
}

Matrix reverse(Matrix A) {
    if (A._n != A._m)
        return Matrix(0, 0);
    Matrix B = A;
    for (int i = 0; i < B._n; ++i) {
        for (int j = 0; j < B._n; ++j) {
            B._data[i].push_back(i == j);
        }
    }
    B._m += B._n;
    makeTriangle(B, true);
    for (int i = B._n - 2; i >= 0; --i) {
        for (int j = i + 1; j < B._n; ++j) {
            if (B._data[i][j] != 0)
                substr(B, i, j, B._data[i][j]);
        }
    }
    for (int i = 0; i < B._n; ++i)
        B._data[i].erase(B._data[i].begin(), B._data[i].begin() + B._n);
    B._m -= B._n;
    return B;
}

double det(Matrix A) {
    if (A._m != A._n)
        return -1;
    makeTriangle(A, false);
    double res = 1;
    for (int i = 0; i < A._n; ++i)
        res *= A._data[i][i];
    return res;
}

double eps = 1e-7;

Matrix jakobi(Matrix A, Matrix b) {
    if (b._m != 1 || b._n != A._m || A._n != A._m)
        return Matrix(0, 0);
    Matrix x(A._n, 1), x0(A._n, 1);
    do {
        for (int i = 0; i < x0._n; ++i) {
            x0._data[i][0] = b._data[i][0];
            for (int j = 0; j < x0._n; ++j)
                x0._data[i][0] -= A._data[i][j] * x._data[j][0] * (i != j);
            x0._data[i][0] /= A._data[i][i];
        }
        swap(x, x0);
    } while ((x - x0).transp().norm() > eps);
    return x;
}

void solveEQ(Matrix A, Matrix b, Matrix method(Matrix, Matrix)) {
    Matrix B = method(A, b);
    cout << "Matrix A:\n" << A << endl;
    cout << "Vector b:\n" << b << endl;
    cout << "Solution x:\n" << B << endl;
    cout << "Check A*x == b:\n" << A * B << endl;
}

int main() {
    cout << fixed << setprecision(3);
    Matrix A = { { 7, 2, 3 }, { -1, 14, 1 }, { 4, 6, 11 } };
    //Matrix A = gilbert(3);
    Matrix b = { { 1 }, { 2 }, { 3 } };
    Matrix C = reverse(A);
    cout << "Gauss method:\n";
    solveEQ(A, b, solveLES);
    cout << "Jakobi method:\n";
    solveEQ(A, b, jakobi);
    cout << "Matrix A^(-1):\n" << C << endl;
    cout << "Check A * (A^-1) == E:\n" << A * C << endl;
    cout << "cond(A) = " << A.norm() * C.norm() << endl;
    cout << "det(A) = " << setprecision(10) << det(A) << endl;

    system("pause");
    return 0;
}