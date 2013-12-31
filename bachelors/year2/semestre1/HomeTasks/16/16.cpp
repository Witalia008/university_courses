#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <limits.h>
#include <algorithm>
#include <iterator>

using namespace std;

struct Tree {
    int data, id;
    vector<Tree*> sons;
};

//check if two trees are equal
bool equals(Tree *where, Tree *what) {
    //check if data and number of sons are equal
    if (where->data != what->data || where->sons.size() != what->sons.size())
        return false;
    //if all sons are equal
    for (int i = 0; i < where->sons.size(); ++i)
        if (!equals(where->sons[i], what->sons[i]))
            return false;
    return true;
}

void search(Tree *where, Tree *what) {
    //for each node check if cur subtree equals to target
    if (equals(where, what)) cout << where->id << endl; else
    //and check for each son
    for (int i = 0; i < where->sons.size(); ++i)
        search(where->sons[i], what);
}

//read tree from cin. it's given by number of vertices and for each vertex it's data and id of parent
void read_tree(vector<Tree*> &a) {
    int n;
    cin >> n;
    a.assign(n, nullptr);
    for (int i = 0; i < n; ++i)
        a[i] = new Tree;
    for (int i = 0; i < n; ++i) {
        a[i]->id = i;
        cin >> a[i]->data;
        int p;
        cin >> p;
        if (p != -1)
            a[p]->sons.push_back(a[i]);
    }
}

vector<Tree*> fst, snd;

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    read_tree(fst);
    read_tree(snd);
    search(fst[0], snd[0]);
    return 0;
}
