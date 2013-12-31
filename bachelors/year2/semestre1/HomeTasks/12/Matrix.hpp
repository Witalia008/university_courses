#pragma once

#include <vector>

using namespace std;

template<class T>
class Node final {
    template<class T>
    friend class Matrix;
    
    Node<T> *nextR, *prevR;
    Node<T> *nextC, *prevC;
    T data;
    int row, col;

    Node(int i, int j, T d) 
        : row(i), col(j), data(d), nextR(nullptr), nextC(nullptr), prevR(nullptr), prevC(nullptr)
    {}
    void connectRowPrev(Node<T>* prev) {
        prevR = prev;
        if (prev != nullptr)
            prev->nextR = this;
    }
    void connectColPrev(Node<T>* prev) {
        prevC = prev;
        if (prev != nullptr)
            prev->nextC = this;
    }
    void connectRowNext(Node<T>* next) {
        nextR = next;
        if (next != nullptr)
            next->prevR = this;
    }
    void connectColNext(Node<T>* next) {
        nextC = next;
        if (next != nullptr)
            next->prevC = this;
    }
};

template<class T>
class Matrix
{
public:
    Matrix(const vector<vector<T>> &);
    Node<T>* getMaximal();
    void removeEl(Node<T>*);
    void removeCol(int);
    void removeRow(int);
    void output();
private:
    vector<Node<T>*> cols, rows;
};

template<class T>
Matrix<T>::Matrix(const vector<vector<T>> &matrix) {
    int n = matrix.size(), m = matrix[0].size();
    vector<Node<T>*> prevs;
    prevs.assign(m, nullptr);
    cols.assign(m, nullptr);
    rows.assign(n, nullptr);
    for (int i = 0; i < n; ++i) {
        Node<T>* last = nullptr;
        for (int j = 0; j < m; ++j)
            if (matrix[i][j]) {
                Node<T>* cur = new Node<T>(i, j, matrix[i][j]);
                
                if (i && prevs[j] != nullptr) cur->connectColPrev(prevs[j]);
                else cols[j] = cur;

                if (last != nullptr) cur->connectRowPrev(last);
                else rows[i] = cur;

                last = cur;
                prevs[j] = cur;
            }
    }
}

template<class T>
Node<T>* Matrix<T>::getMaximal() {
    Node<T>* res = nullptr;
    for (int i = 0; i < rows.size(); ++i) {
        for (Node<T>* j = rows[i]; j != nullptr; j = j->nextR)
            if (res == nullptr || j->data > res->data)
                res = j;
    }
    return res;
}

template<class T>
void Matrix<T>::removeRow(int index) {
    for (Node<T>* j = rows[index]; j != nullptr; ) {
        if (j->prevC != nullptr)
            j->prevC->connectColNext(j->nextC);
        else
            cols[j->col] = j->nextC;
        Node<T>* nx = j->nextR;
        delete j;
        j = nx;
    }
    rows.erase(rows.begin() + index);
    for (int i = index; i < rows.size(); ++i)
        for (Node<T>* j = rows[i]; j != nullptr; j = j->nextR)
            --j->row;
}

template<class T>
void Matrix<T>::removeCol(int index) {
    for (Node<T>* j = cols[index]; j != nullptr; ) {
        if (j->prevR != nullptr)
            j->prevR->connectRowNext(j->nextR);
        else
            rows[j->row] = j->nextR;
        Node<T>* nx = j->nextC;
        delete j;
        j = nx;
    }
    cols.erase(cols.begin() + index);
    for (int j = index; j < cols.size(); ++j)
        for (Node<T>* i = cols[j]; i != nullptr; i = i->nextC)
            --i->col;
}

template<class T>
void Matrix<T>::removeEl(Node<T>* target) {
    int i = target->row, j = target->col;
    removeCol(j);
    removeRow(i);
}

template<class T>
void Matrix<T>::output() {
    for (int i = 0; i < rows.size(); ++i) {
        Node<T>* cur = rows[i];
        for (int j = 0; j < cols.size(); ++j)
            if (cur != nullptr && cur->col == j) {
                cout << cur->data << " ";
                cur = cur->nextR;
            } else {
                cout << T() << " ";
            }
        cout << endl;
    }
}