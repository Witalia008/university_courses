#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

/** Class Matrix stores rectangle matrix and it's dimensions
  */
class Matrix {
private:
    unsigned int rows, cols;
    vector<vector<double>> matr;
    vector<double> restoreVarVals(vector<vector<double>>&) throw();
public:
    Matrix();
    Matrix(unsigned int, unsigned int);
    Matrix(const vector<vector<double>>&);
    vector<double> solveRotation() throw();
    vector<double> solveGauss() throw();
    vector<double> solveKramer() throw();
    void set(unsigned int x, unsigned int y, double value) throw();
    void resize(unsigned int _rows, unsigned int _cols);
    void expandRows(vector<double> values);
    void expandCols(vector<double> values);
    void swapRows(unsigned int r1, unsigned int r2) throw();
    void swapCols(unsigned int c1, unsigned int c2) throw();
    double determinant(int) throw();
};

#endif