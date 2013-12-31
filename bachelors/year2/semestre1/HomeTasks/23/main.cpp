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


using namespace std;
using namespace std::chrono;

using ll = long long;
const int Inf = 1000000000;

class Type {
    friend class Matrix;
    string name;
    const static vector<string> names;
    Type() { name = names[0]; }
    Type(string _n) : name(_n) {}
    Type(int num) : name(names[num]) {}
    void *read(istream &in) {
        if (name == "bool") {
            bool x;
            in >> x;
            return new bool(x);
        }
        if (name == "char") {
            char x;
            in >> x;
            return new char(x);
        }
        if (name == "short") {
            short x;
            in >> x;
            return new short(x);
        }
        if (name == "int") {
            int x;
            in >> x;
            return new int(x);
        }
        if (name == "double") {
            double x;
            in >> x;
            return new double(x);
        }
        if (name == "string") {
            string x;
            do {
                getline(in, x);
            } while (x == "");
            return new string(x);
        }
    }
    void output(ostream& out, void *data) {
        if (name == "bool")
            out << " " << *((bool*)data);
        if (name == "int")
            out << " " << *((int*)data);
        if (name == "short")
            out << " " << *((short*)data);
        if (name == "char")
            out << " " << *((char*)data);
        if (name == "string")
            out << endl << *((string*)data) << endl;
        if (name == "double")
            out << " " << *((double*)data);
    }
    void *neww(void * data) {
        if (name == "bool")
            return new bool(*((bool*)data));
        if (name == "int")
            return new int(*((int*)data));
        if (name == "short")
            return new short(*((short*)data));
        if (name == "char")
            return new char(*((char*)data));
        if (name == "double")
            return new double(*((double*)data));
        if (name == "bool")
            return new string(*((string*)data));
    }
    void delete_(void *&data) {
        if (data == nullptr)
            return;
        if (name == "int")
            delete ((int*)data);
        if (name == "bool")
            delete ((bool*)data);
        if (name == "short")
            delete ((short*)data);
        if (name == "char")
            delete ((char*)data);
        if (name == "double")
            delete ((double*)data);
        if (name == "string")
            delete ((string*)data);
        data = nullptr;
    }
    bool can_change(Type other) {
        if (name == "string")
            return other.name == "string";
        return other.name != "string";
    }
    void *convert(void *data, Type other) {
        void * res = other.neww(data);
        delete_(data);
        return res;
    }
    int number() {
        return find(names.begin(), names.end(), name) - names.begin();
    }
public:
    static void show_types() {
        cout << "Types are:\n";
        for (int i = 0; i < names.size(); ++i)
            cout << i << ". " << names[i] << endl;
    }
};

const vector<string> Type::names = { "double", "int", "short", "bool", "char", "string" };

class Matrix {
    vector<vector<void*>> cols;
    vector<vector<Type>> types;
public:
    void create(int n, int m) {
        cols.resize(m);
        types.resize(m);
        for (int i = 0; i < m; ++i) {
            cols[i].assign(n, nullptr);
            types[i].assign(n, Type());
        }
    }
    void read(string fname) {
        ifstream in(fname);
        if (!in.good()) {
            cout << "No such file\n";
            return;
        }
        int n, m;
        in >> n >> m;
        create(n, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int t;
                in >> t;
                if (t >= 0) {
                    Type cur(t);
                    cols[j][i] = cur.read(in);
                    types[j][i] = cur;
                }
            }
        }
        in.close();
    }
    void write(string fname) {
        ofstream out(fname);
        if (!out.good()) {
            cout << "No such file\n";
            return;
        }
        out << (cols.size() ? cols[0].size() : 0) << " " << cols.size() << endl;
        if (cols.size()) {
            for (int i = 0; i < cols[0].size(); ++i) {
                for (int j = 0; j < cols.size(); ++j) {
                    if (cols[j][i] != nullptr) {
                        out << " " << types[j][i].number();
                        types[j][i].output(out, cols[j][i]);
                    }
                    else out << -1 << " ";
                }
            }
        }
    }
    void delete_col(int num) {
        if (num >= 0 && num < cols.size()) {
            for (int i = 0; i < cols[num].size(); ++i)
                types[num][i].delete_(cols[num][i]);
            cols.erase(num + cols.begin());
            types.erase(num + types.begin());
        }
        else {
            cout << "Wrong number of column\n";
        }
    }
    void delete_row(int num) {
        if (cols.size() && num >= 0 && num < cols[0].size()) {
            for (int i = 0; i < cols.size(); ++i) {
                types[i][num].delete_(cols[i][num]);
                cols[i].erase(num + cols[i].begin());
                types[i].erase(num + types[i].begin());
            }
            if (cols[0].size() == 0)
                cols.clear();
        }
        else {
            cout << "Wrong number of row\n";
        }
    }
    void delete_cell(int i, int j) {
        if (i >= 0 && j >= 0 && j < cols.size() && i < cols[0].size()) {
            types[j][i].delete_(cols[j][i]);
        }
        else {
            cout << "Wrong coordinates\n";
        }
    }
    void change_cell(int i, int j) {
        if (i >= 0 && j >= 0 && j < cols.size() && i < cols[0].size()) {
            Type::show_types();
            int t;
            cin >> t;
            types[j][i] = Type(t);
            cols[j][i] = types[j][i].read(cin);
        }
        else {
            cout << "Wrong coordinates\n";
        }
    }
    void add_col(int pos) {
        if (pos < 0 || pos > cols.size()) return;
        Type::show_types();
        int n;
        if (cols.size())
            n = cols[0].size();
        else {
            cols.resize(1);
            cout << "Enter row size: ";
            cin >> n;
        }
        vector<void*> cur_col;
        vector<Type> tps;
        for (int i = 0; i < n; ++i) {
            int t;
            cin >> t;
            Type cur(t);
            cur_col.push_back(cur.read(cin));
            tps.push_back(cur);
        }
        cols.insert(cols.begin() + pos, cur_col);
        types.insert(types.begin() + pos, tps);
    }
    void add_row(int pos) {
        Type::show_types();
        int m;
        if (cols.size())
            m = cols.size();
        else {
            cout << "Enter number of cols: ";
            cin >> m;
        }
        cols.resize(m);
        types.resize(m);
        for (int i = 0; i < m; ++i) {
            int t;
            cin >> t;
            Type cur(t);
            cols[i].insert(cols[i].begin() + pos, cur.read(cin));
            types[i].insert(types[i].begin() + pos, cur);
        }
    }
    void change_row(int pos) {
        delete_row(pos);
        add_row(pos);
    }
    void change_col(int pos) {
        delete_col(pos);
        add_col(pos);
    }
    void convert_cell(int i, int j, int to) {
        if (i >= 0 && j >= 0 && j < cols.size() && i < cols[0].size()) {
            if (types[j][i].can_change(Type(to)))
                cols[j][i] = types[j][i].convert(cols[j][i], Type(to));
        }
        else {
            cout << "Wrond coordinates\n";
        }
    }
    void convert_col(int pos, int to) {
        if (pos >= 0 && pos < cols.size()) {
            for (int i = 0; i < cols[pos].size(); ++i) {
                if (types[pos][i].can_change(Type(to))) {
                    cols[pos][i] = types[pos][i].convert(cols[pos][i], Type(to));
                }
            }
        }
        else {
            cout << "Wrond column number\n";
        }
    }
    void convert_row(int pos, int to) {
        if (cols.size() && pos >= 0 && pos < cols[0].size()) {
            for (int j = 0; j < cols.size(); ++j) {
                if (types[j][pos].can_change(Type(to)))
                    cols[j][pos] = types[j][pos].convert(cols[j][pos], Type(to));
            }
        }
        else {
            cout << "Wrond coordinates\n";
        }
    }
    void show() {
        if (cols.size() != 0) {
            for (int i = 0; i < cols[0].size(); ++i) {
                for (int j = 0; j < cols.size(); ++j) {
                    types[j][i].output(cout, cols[j][i]);
                    if (j == cols.size() - 1)
                        cout << endl;
                    else cout << " ";
                }
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
    Matrix M;
    int oper = 0;
    for (; oper != -1;) {
        cout << "1. Read from file\n";
        cout << "2. Write to file\n";
        cout << "3. Change cell\n";
        cout << "4. Delete cell\n";
        cout << "5. Add row\n";
        cout << "6. Delete row\n";
        cout << "7. Change row\n";
        cout << "8. Add col\n";
        cout << "9. Delete col\n";
        cout << "10. Change col\n";
        cout << "11. Show\n";
        cout << "12. Convert cell type\n";
        cout << "13. Convert col type\n";
        cout << "14. Convert row type\n";
        cout << "-1. Exit\n";
        cin >> oper;

        if (oper == 1 || oper == 2) {
            cout << "Enter file name: ";
            string name;
            cin >> name;
            if (oper == 1)
                M.read(name);
            if (oper == 2)
                M.write(name);
        }
        if (oper == 3 || oper == 4) {
            cout << "Enter coordinates: ";
            int i, j;
            cin >> i >> j;
            if (oper == 3)
                M.change_cell(i, j);
            if (oper == 4)
                M.delete_cell(i, j);
        }
        if (oper >= 5 && oper <= 7) {
            cout << "Enter number of row: ";
            int pos;
            cin >> pos;
            if (oper == 5)
                M.add_row(pos);
            if (oper == 6)
                M.delete_row(pos);
            if (oper == 7)
                M.change_row(pos);
        }
        if (oper >= 8 && oper <= 10) {
            cout << "Enter number of col: ";
            int pos;
            cin >> pos;
            if (oper == 8)
                M.add_col(pos);
            if (oper == 9)
                M.delete_col(pos);
            if (oper == 10)
                M.change_col(pos);
        }
        if (oper == 11)
            M.show();
        if (oper == 12) {
            cout << "Enter coordinates: ";
            int i, j, to;
            cin >> i >> j;
            Type::show_types();
            cin >> to;
            M.convert_cell(i, j, to);
        }
        if (oper == 13) {
            int pos, to;
            cout << "Enter column id: ";
            cin >> pos;
            Type::show_types();
            cin >> to;
            M.convert_col(pos, to);
        }
        if (oper == 14) {
            int pos, to;
            cout << "Enter row id: ";
            cin >> pos;
            Type::show_types();
            cin >> to;
            M.convert_row(pos, to);
        }
    }
    return 0;
}