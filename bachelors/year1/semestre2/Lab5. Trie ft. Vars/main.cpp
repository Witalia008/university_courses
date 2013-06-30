#include <iostream>
#include "variables.h"

using namespace std;

var_set a;

int main() {
    for (;;) {
        a = get_from_file("vars.txt");
        list_type cur_var;
        cin >> cur_var.name;
        if (cur_var.name == "exit") {
            break;
        }
        if (cur_var.name.size() > 2 && cur_var.name.substr(cur_var.name.size() - 2, 2) == "::") {
            out_from_namesp(a, cur_var.name, cout);
            continue;
        }
        cin >> cur_var.value;
        if (cur_var.name == "?") {
            List *where = find_variable(a, cur_var.second);
            if (where == NULL) {
                cout << "No such variable\n";
            } else {
                cout << where->data.name << " = " << where->data.value << endl;
            }
            continue;
        }
        set_var(a, cur_var);
        out_to_file(a, "vars.txt");
    }
    return 0;
}
