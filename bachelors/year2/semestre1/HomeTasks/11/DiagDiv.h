#pragma once
#include <string>
#include <fstream>
#include <vector>

using namespace std;


class Point {
protected:
    int x, y;
public:
    Point() {}
    Point(int _x, int _y) : x(_x), y(_y) {}
    int X() { return x; };
    int Y() { return y; };
};

vector<Point> readPoints(string fname);

const double InfL = 1e9;
typedef double (*cmpFunc)(double, double);

typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef vector<vector<pair<int, double>>> vvd;

double dist(Point, Point);
pair<int, double> findDivision(vector<Point>&, int, int, cmpFunc, vvd&);
void calcDiadDivision(ostream&, vector<Point>, cmpFunc);
vector<pair<int, int>> getPath(vvd&, int, int);