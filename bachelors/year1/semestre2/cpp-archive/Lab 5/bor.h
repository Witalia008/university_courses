#ifndef BOR_H
#define BOR_H

#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <memory.h>
#include <iostream>
#include <map>
#include "list.h"

using namespace std;

struct Bor {
    map<int, Bor*> next;
    List *var;
    Bor () {
        var = NULL;
        next.clear();
    }
};

Bor *find_add(Bor *root, string word, bool needAdd);
void set_value(Bor *root, List *var);
void sub_tree_out(Bor *v, ostream &out);

#endif // BOR_H
