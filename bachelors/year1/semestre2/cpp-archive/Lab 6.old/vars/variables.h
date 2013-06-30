#ifndef VARIABLES_INCLUDED
#define VARIABLES_INCLUDED

#include <fstream>
#include "list.h"
#include "bor.h"

struct var_set {
    Bor *trie;
    List *vars;
    var_set() {
        trie = new Bor();
        vars = NULL;
    }
};

void check_namespace(string &s);
var_set get_from_file(istream &inp);
var_set get_from_file(string file_name);
List *find_variable(var_set t, string var_name);
void out_from_namesp(var_set t, string namesp, ostream &out);
string variable_value(var_set t, string name);
bool add_var(var_set &t, list_type var);
void set_var(var_set &t, list_type var);
void out_to_file(var_set t, ostream &out);
void out_to_file(var_set t, string filename);


#endif // VARIABLES_INCLUDED
