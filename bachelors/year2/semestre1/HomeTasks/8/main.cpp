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

class Spline {
    vector<double> x, y;
    struct data {
        double a, b, c, d;
    };
    vector<data> rest_data;
public:
    Spline() {
        this->read();
        this->build();
    }
    void read() {
        int n;
        cin >> n;
        x.resize(n);
        y.resize(n);
        for (int i = 0; i < n; ++i)
            cin >> x[i] >> y[i];
    }
    void build() {
        int n = x.size();
        if (n < 2) return;
        rest_data.resize(n);

        for (int i = 0; i < n; ++i)
            rest_data[i].a = y[i];

        vector<double> alpha(n, 0), betta(n, 0);
        rest_data[0].c = 0;
        double A, B, C, F;
        for (int i = 1; i < n - 1; ++i) {
            double h_i = x[i] - x[i - 1], h_i1 = x[i + 1] - x[i];
            A = h_i;
            B = h_i1;
            C = 2. * (h_i + h_i1);
            F = 6. * ((y[i + 1] - y[i]) / h_i1 - (y[i] - y[i - 1]) / h_i);
            double z = (C + A * alpha[i - 1]);
            alpha[i] = -B / z;
            betta[i] = (F - A * betta[i - 1]) / z;
        }

        rest_data[n - 1].c = (F - A * betta[n - 2]) / (C + A * alpha[n - 2]);

        for (int i = n - 2; i > 0; --i)
            rest_data[i].c = alpha[i] * rest_data[i + 1].c + betta[i];

        for (int i = n - 1; i > 0; --i) {
            double h_i = x[i] - x[i - 1];
            rest_data[i].d = (rest_data[i].c - rest_data[i - 1].c) / h_i;
            rest_data[i].b = (y[i] - y[i - 1]) / h_i + (2 * rest_data[i].c + rest_data[i - 1].c) * h_i / 6;
        }
    }
    double f(double X) {
        int pos;
        if (X < x[0])
            pos = 1;
        else if (X > x.back())
            pos = x.size() - 1;
        else {
            int l = 0, r = x.size() - 1;
            while (l < r - 1) {
                int mid = (l + r) >> 1;
                if (X <= x[mid])
                    r = mid;
                else
                    l = mid;
            }
            pos = r;
        }
        double h_x = X - x[pos];
        return rest_data[pos].a + rest_data[pos].b * h_x + rest_data[pos].c * pow(h_x, 2) / 2 + rest_data[pos].d * pow(h_x, 3) / 6;
    }
};

//#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    Spline a;
    double x;
    cin >> x;
    cout << a.f(x) << endl;
    return 0;
}