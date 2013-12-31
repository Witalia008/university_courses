#include "Matrix.h"

double sqr(double a) { return a * a; }
double Abs(double a) { return a < 0 ? -a : a; }

Matrix::Matrix() {
    rows = cols = 0;
    matr.clear();
}

Matrix::Matrix(unsigned int _rows, unsigned int _cols) {
    resize(_rows, _cols);
    for (auto& i: matr)
        for (auto& j : i)
            j = 0;
}

Matrix::Matrix(const vector<vector<double>>& m) {
    rows = m.size();
    matr.resize(rows);
    cols = 0;
    for (int i = 0; i < rows; i++) {
        matr[i].clear();
        matr[i].insert(matr[i].end(), m[i].begin(), m[i].end());
        cols = max(cols, static_cast<unsigned int>(m[i].size()));
    }
    /* be sure that all rows have the same number of elements */
    for (int i = 0; i < rows; i++)
        matr[i].resize(cols);
}

void Matrix::set(unsigned int x, unsigned int y, double value) throw() {
    if (x >= rows || y >= cols)
        throw runtime_error("Out of bounds");
    matr[x][y] = value;
}

void Matrix::resize(unsigned int _rows, unsigned int _cols) {
    rows = _rows;
    cols = _cols;
    matr.resize(rows);
    for (auto& i : matr)
        i.resize(cols);
}

/* Add new row in the end of the matrix */
void Matrix::expandRows(vector<double> values) {
    if (values.size() > cols) {
        cols = values.size();
        resize(rows, cols);
    }
    rows++;
    matr.push_back(values);
    matr.back().resize(cols);
}

/* Add new column as the last column in matrix */
void Matrix::expandCols(vector<double> values) {
    cols++;
    for (int i = 0; i < rows; i++) {
        matr[i].resize(cols);
        matr[i][cols - 1] = (i < values.size() ? values[i] : 0);
    }
}

void Matrix::swapRows(unsigned int r1, unsigned int r2) throw() {
    if (r1 >= rows || r2 >= rows)
        throw runtime_error("Out of bounds");
    matr[r1].swap(matr[r2]);
}

void Matrix::swapCols(unsigned int c1, unsigned int c2) throw() {
    if (c1 >= cols || c2 >= cols)
        throw runtime_error("Out of bounds");
    for (auto& i : matr)
        swap(i[c1], i[c2]);
}


/** Calculates determinant of matrix.
  * As an argument takes number of columns to ignore (for case where matrix is not square one)
  */
double Matrix::determinant(int extra = 0) throw() {
    vector<int> col;
    for (int i = 0; i < cols - extra; i++)
        col.push_back(i);
    if (col.size() != rows)
        throw runtime_error("Matrix is not square");
    double ans = 0;
    do {
        double cur = 1;
        int S = 0;
        for (int i = 0; i < col.size(); i++) {
            cur *= matr[i][col[i]];
            for (int j = 0; j < i; j++)
                S += col[j] > col[i];
        }
        ans += (S % 2 ? 1 : -1) * cur;
    } while (next_permutation(col.begin(), col.end()));
    return ans;
}

/** Restores solutions of equation system from triangular matrix.
  * Throws runtime error if matrix has zero or infinite number of solutions.
  */
vector<double> Matrix::restoreVarVals(vector<vector<double>>& m) throw() {
    vector<double> sol(cols - 1);
    for (int curVar = cols - 2; curVar >= 0; curVar--) {
        sol[curVar] = m[curVar][cols - 1];
        for (int varSub = curVar + 1; varSub < cols - 1; varSub++)
            sol[curVar] -= m[curVar][varSub] * sol[varSub];
        if (Abs(m[curVar][curVar]) < 1e-9) {
            if (Abs(sol[curVar]) < 1e-9)
                throw runtime_error("Infinit number of solutions");
            else
                throw runtime_error("No solutions");
        }
        sol[curVar] /= m[curVar][curVar];
    }
    return sol;
}

/** Solves equation system using rotation method
  * Throws runtime error if matrix has zero or infinite number of solutions.
  */
vector<double> Matrix::solveRotation() throw() {
    if (rows != cols - 1 || rows < 1)
        throw runtime_error("Not enough equations");
    vector<vector<double>> m = matr;
    for (int curVar = 0; curVar < cols - 2; curVar++) {
        for (int rowToReduce = curVar + 1; rowToReduce < rows; rowToReduce++) {
            if (Abs(m[curVar][curVar]) < 1e-9)
                throw runtime_error("No solutions");
            double cos_phi = m[curVar][curVar] / sqrt(sqr(m[curVar][curVar]) + sqr(m[rowToReduce][curVar]));
            double sin_phi = m[rowToReduce][curVar] / sqrt(sqr(m[curVar][curVar]) + sqr(m[rowToReduce][curVar]));
            for (int colReduce = curVar; colReduce < cols; colReduce++) {
                double temp = m[curVar][colReduce];
                m[curVar][colReduce] = cos_phi * temp + sin_phi * m[rowToReduce][colReduce];
                m[rowToReduce][colReduce] = -sin_phi * temp + cos_phi * m[rowToReduce][colReduce];
            }
        }
    }
    return restoreVarVals(m);
}
/** Solves equation system using Gauss method
  * Throws runtime error if matrix has zero or infinite number of solutions.
  */
vector<double> Matrix::solveGauss() throw() {
    if (rows != cols - 1 || rows < 1)
        throw runtime_error("Not enough equations");
    vector<vector<double>> m = matr;
    for (int curVar = 0; curVar < cols - 2; curVar++) {
        for (int rowToReduce = curVar + 1; rowToReduce < rows; rowToReduce++) {
            if (Abs(m[curVar][curVar]) < 1e-9)
                throw runtime_error("No solutions");
            double reduceLev = m[rowToReduce][curVar] / m[curVar][curVar];
            for (int colReduce = curVar; colReduce < cols; colReduce++) {
                m[rowToReduce][colReduce] -= reduceLev * m[curVar][colReduce];
            }
        }
    }
    return restoreVarVals(m);
}
/** Solves equation system using Kramers method
  * Throws runtime error if matrix has zero or infinite number of solutions.
  */
vector<double> Matrix::solveKramer() throw() {
    if (rows != cols - 1 || rows < 1)
        throw runtime_error("Not enough equations");
    double det = determinant(1);
    if (Abs(det) < 1e-9)
        throw runtime_error("No solutions");
    vector<double> res;
    for (int i = 0; i < cols - 1; i++) {
        swapCols(i, cols - 1);
        res.push_back(determinant(1) / det);
        swapCols(i, cols - 1);
    }
    return res;
}