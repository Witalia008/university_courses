#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <cmath>
#include <stack>

#include "logging.h"

using namespace std;

struct pt {
    float x, y;
    pt() {}
    pt(float _x, float _y) : x(_x), y(_y) {}
    void rotate(float ang);
    void move(pt dir, float len);
};

void pt::rotate(float ang) {
    float xx = cos(ang) * x - sin(ang) * y;
    float yy = sin(ang) * x + cos(ang) * y;
    x = xx; y = yy;
}

void pt::move(pt dir, float len) {
    float len1 = sqrt(dir.x * dir.x + dir.y * dir.y);
    this->x += dir.x * len / len1;
    this->y += dir.y * len / len1;
}

const float PI = acos(0.0);

class Fractal {
    int depth;
    double angle;
    double step_len;
    string axiom;
    vector<pair<string, string>> rules;
    string interpret;
    Fractal();
    string get_interpr(int);
    vector<pt> get_pts(pt);
public:
    Fractal(string filename);
    pair<float*, int> get_points(pt start);
};


Fractal::Fractal(string filename) {
    fstream in(filename, fstream::in);
    if (in.is_open()) {
        in >> depth >> angle;
        in >> axiom;
        angle = (angle / 90) * PI;
        for (;;) {
            string x, y;
            in >> x >> y;
            if (x == "" || y == "")
                break;
            rules.push_back(make_pair(x, y));
        }
        interpret = "";
        step_len = 1;
        in.close();
    }
}

string Fractal::get_interpr(int n) {
    string res = axiom;
    for (int step = 0; step < depth; ++step) {
        string s = "";
        for (int i = 0; i < res.size();) {
            bool found = false;
            for (int j = 0; j < rules.size(); ++j)
                if (res.substr(i, rules[j].first.size()) == rules[j].first) {
                    s += rules[j].second;
                    i += rules[j].first.size();
                    found = true;
                    break;
                }
            if (!found)
                s += res[i++];
        }
        res = s;
    }
    return res;
}

vector<pt> Fractal::get_pts(pt start) {
    stack<pair<pt, pt>> st;
    pt cur_pos = start;
    pt dir(0, 1);
    vector<pt> res;
    for (int i = 0; i < interpret.size(); ++i) {
        char cur = interpret[i];
        if (cur == '[') {
            st.push(make_pair(cur_pos, dir));
        } else if (cur == ']') {
            cur_pos = st.top().first;
            dir = st.top().second;
            st.pop();
        } else if (cur == 'f') {
            cur_pos.move(dir, step_len);
        } else if (cur == 'F') {
            res.push_back(cur_pos);
            cur_pos.move(dir, step_len);
            res.push_back(cur_pos);
        } else if (cur == '|') {
            dir.rotate(PI);
        } else if (cur == '+') {
            dir.rotate(angle);
        } else if (cur == '-') {
            dir.rotate(-angle);
        } else if (cur == '^') {
        } else if (cur == '&') {
            dir.rotate(PI);
        } else if (cur == '\\') {
        } else if (cur == '/') {
        }
    }
    return res;
}

pair<float*, int> Fractal::get_points(pt start) {
    interpret = get_interpr(depth);
    vector<pt> res = get_pts(start);
    float *r = new float[res.size() * 3];
    float max_x = -1e5, max_y = -1e5;
    float min_x = 1e5, min_y = 1e5;
    for (pt i : res) {
        max_x = max(max_x, i.x);
        max_y = max(max_y, i.y);
        min_x = min(min_x, i.x);
        min_y = min(min_y, i.y);
    }
    float dx = (max_x - min_x) / 1.78, dy = (max_y - min_y);
    float delta = max(dx, dy);
    float mid_x = (min_x + max_x) / 2;
    for (int i = 0; i < res.size(); ++i) {
        r[i * 3] = (res[i].x - mid_x) / delta;
        r[i * 3 + 1] = -0.9 + 1.8 * (res[i].y - min_y) / delta;
        r[i * 3 + 2] = 0;
    }
    return make_pair(r, res.size() * 3);
}