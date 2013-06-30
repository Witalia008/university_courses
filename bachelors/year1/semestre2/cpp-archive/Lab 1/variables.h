#ifndef VARIABLES_INCLUDED
#define VARIABLES_INCLUDED 1

#include "head.h"

typedef vector<string> vs;
struct VarSet
{
    int n;
    vs name, value;
};

void toFile (VarSet all);

void fromFile (VarSet &all);

void chk_(string &a);

int find_var (string _name, VarSet all);

bool add_var (string _name, string _value, VarSet &all);

bool del_var (string _name, VarSet &all);

#endif // VARIABLES_INCLUDED

