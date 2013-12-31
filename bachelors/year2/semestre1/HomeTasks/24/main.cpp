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


using namespace std;
using namespace std::chrono;

vector<pair<char, int>> count_freq(string filename) {
    ifstream in(filename);
    unordered_map<char, int> dict;
    while (!in.eof()) {
        string s;
        getline(in, s);
        for (char i : s)
            if (i > 0)
                dict[i]++;
    }
    return vector<pair<char, int>>(dict.begin(), dict.end());
}

struct NodeH {
    char symb;
    int freq;
    NodeH *parent;
    NodeH *l_son, *r_son;
    NodeH(char s, int f) 
        : symb(s), freq(f), parent(nullptr), l_son(nullptr), r_son(nullptr)
    {}
};

NodeH* unite(NodeH* l, NodeH* r) {
    NodeH* res = new NodeH(0, l->freq + r->freq);
    res->l_son = l;
    res->r_son = r;
    l->parent = r->parent = res;
    return res;
}

string get_code(NodeH* leaf) {
    if (leaf == nullptr || leaf->symb == 0)
        return "";
    string res = "";
    while (leaf->parent != nullptr) {
        res += leaf == leaf->parent->r_son ? "1" : "0";
        leaf = leaf->parent;
    }
    return res;
}

void output(NodeH* t) {
    if (t == nullptr) {
        cout << "NIL";
        return;
    }
    cout << "{" << (t->symb == 0 ? "" : ""+t->symb) << ", " << t->freq << "}";
    cout << "(";
    output(t->l_son);
    cout << ",";
    output(t->r_son);
    cout << ")";
}

void build_H_tree(string filename, bool pred(char)) {
    vector<pair<char, int>> freq_tbl = count_freq(filename);
    auto cmp = [](NodeH* x, NodeH* y) {
        return x->freq > y->freq;
    };
    priority_queue<NodeH*, vector<NodeH*>, decltype(cmp)> q(cmp);
    vector<NodeH*> leaves;
    for (auto i : freq_tbl) 
        if (pred(i.first)) {
            leaves.push_back(new NodeH(i.first, i.second));
            q.push(leaves.back());
        }
    while (q.size() != 1) {
        NodeH* fst = q.top(); q.pop();
        NodeH* snd = q.top(); q.pop();
        q.push(unite(fst, snd));
    }
    output(q.top()); cout << endl;
    for (auto i : leaves)
        cout << i->symb << " " << get_code(i) << endl;
}

//#define ONLINE_JUDGE
int main () {
#ifndef ONLINE_JUDGE
    //freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    build_H_tree("input.txt", [](char q) { return true; });
    return 0;
}