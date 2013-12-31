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


using namespace std;
using namespace std::chrono;

using Point = pair<double, double>;

const int NUM_OF_POINTS = 100;
const int NUM_OF_GENERS = 20000;
const double LEFT_MOST = -1e7;
const double RIGHT_MOST = 1e7;

vector<double> first_gen() {
    vector<double> res;
    for (int i = 0; i < NUM_OF_POINTS; ++i)
        res.push_back((RIGHT_MOST - LEFT_MOST) * (1.0 * rand()) / RAND_MAX + LEFT_MOST);
    return res;
}

vector<Point> gen_points(vector<double> X, double func(double)) {
    vector<Point> res;
    for (double x : X)
        res.push_back(make_pair(x, func(x)));
    return res;
}

vector<double> new_generation(vector<Point> gen) {
    vector<double> res;
    int n = gen.size();
    for (int i = 0; i < n; ++i) {
        int fst = rand() % (n / 2), snd = 0;
        do {
            snd = rand() % (n / 2);
        } while (snd == fst);
        res.push_back((gen[fst].first + gen[snd].first) / 2);
    }
    return res;
}

Point get_max(double func(double)) {
    vector<double> generation = first_gen();
    
    for (int i = 0; i < NUM_OF_GENERS; ++i) {
        vector<Point> pts = gen_points(generation, func);

        sort(pts.begin(), pts.end(), [](const Point &a, const Point &b) {
            return a.second < b.second - DBL_EPSILON || fabs(a.second - b.second) < DBL_EPSILON && a.first < b.first;
        });
        
        generation = new_generation(pts);
    }
    double res_x = 0;
    for (int i = 1; i < generation.size(); ++i) {
        if (func(generation[i]) < func(generation[res_x]))
            res_x = i;
    }
    return make_pair(generation[res_x], func(generation[res_x]));
}

#define ONLINE_JUDGE
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    auto func = [](double x) -> double {
        return 18 * pow(x, 2) + 25 * x - 17;
    };
    Point min_pt = get_max(func);
    cout << min_pt.first << " " << min_pt.second << endl;
    system("pause");
    return 0;
}