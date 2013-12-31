#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <set>
#include <algorithm>
#include <queue>
#pragma comment(linker, "/STACK:64000000")

using namespace std;

const int N = 220;

typedef pair<int, int> pii;

bool grid[N * 2][N * 2];

struct Point {
    int x, y;
    Point () : x(0), y(0) {}
    Point(int _x, int _y) : x(_x), y(_y) {}
};

vector<pair<Point, Point>> rects;
vector<pii> allX, allY;

void add(Point a) {
    allX.push_back(make_pair(a.x, 0));
    allY.push_back(make_pair(a.y, 0));
}

void zip_coords() {
    sort(allX.begin(), allX.end());
    sort(allY.begin(), allY.end());
    if (allX.size())
        allX[0].second = allY[0].second = 1;
    for (int i = 1; i < allX.size(); ++i) {
        allX[i].second = allX[i - 1].second + (allX[i].first != allX[i - 1].first) * 2;
        allY[i].second = allY[i - 1].second + (allY[i].first != allY[i - 1].first) * 2;
    }
}

Point get_coords(Point a) {
    Point res;
    auto pred = [](const pii a, const int b) { return a.first < b; };
    res.x = (*lower_bound(allX.begin(), allX.end(), a.x, pred)).second;
    res.y = (*lower_bound(allY.begin(), allY.end(), a.y, pred)).second;
    return res;
}

void fill_rect(pair<Point, Point> a) {
    if (a.first.x > a.second.x)
        swap(a.first.x, a.second.x);
    if (a.first.y > a.second.y)
        swap(a.first.y, a.second.y);
    for (int i = a.first.x; i <= a.second.x; ++i)
        grid[i][a.first.y] = grid[i][a.second.y] = true;
    for (int i = a.first.y; i <= a.second.y; ++i)
        grid[a.first.x][i] = grid[a.second.x][i] = true;
}

bool good_point(int x, int y) {
    return x >= 0 && y >= 0 && x < N * 2 && y < N * 2;
}

const int mx[] = {0, 0, 1, -1};
const int my[] = {-1, 1, 0, 0};

void dfs(int i, int j) {
    grid[i][j] = true;
    for (int k = 0; k < 4; ++k)
        if (good_point(i + mx[k], j + my[k]) && grid[i + mx[k]][j + my[k]] == false)
            dfs(i + mx[k], j + my[k]);
}

int get_planes_numb() {
    int res = 0;
    for (int i = 0; i < N * 2; ++i)
        for (int j = 0; j < N * 2; ++j)
            if (!grid[i][j]) {
                dfs(i, j);
                ++res;
            }
    return res;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    cin >> n;
    rects.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> rects[i].first.x >> rects[i].first.y >> rects[i].second.x >> rects[i].second.y;
        add(rects[i].first);
        add(rects[i].second);
    }
    zip_coords();
    for (int i = 0; i < n; ++i) {
        rects[i].first = get_coords(rects[i].first);
        rects[i].second = get_coords(rects[i].second);
        fill_rect(rects[i]);
    }
    cout << get_planes_numb() << endl;
    return 0;
}
