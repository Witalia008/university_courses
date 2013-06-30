#ifndef VARIABLES_INCLUDED
#define VARIABLES_INCLUDED

#include <fstream>
#include "list.h"

struct var_set {
    List *name, *value;
};

var_set get_from_file (string filename);
list_type get_namespace (list_type name);
var_set find_variable (var_set t);
var_set get_from_namesp (var_set t, list_type name);
bool add_var (var_set &t, list_type name, list_type val);
bool set_var (var_set &t, list_type name, list_type val);
void out_to_file (var_set t, string filename);
bool is_good_variable (list_type name);
void out_by_namespace (var_set t, string filename);


#endif // VARIABLES_INCLUDED
