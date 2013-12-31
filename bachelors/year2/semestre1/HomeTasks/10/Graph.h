#pragma once
#include <vector>
#include <stack>
#include <fstream>
#include <map>
#include <algorithm>

using namespace std;

class Graph {
protected:
    int V, E;
    vector<vector<pair<int, int>>> adj;
public:
    void addRib(int, int, int);
    void readIncidencyList(string);
    bool isEuler();
    vector<int> euler();
};