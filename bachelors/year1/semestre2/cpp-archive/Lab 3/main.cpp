#include <iostream>
#include "list.h"
#include "variables.h"

using namespace std;

var_set a;

int main()
{
    for (;;) {
        a = get_from_file("vars.txt");
        string name, val;
        cin >> name >> val;
        if (name == "OK") break;
        if (name == "namespace") {
            var_set tmp = get_from_namesp(a, val);
            while (tmp.name) {
                cout << get_value(tmp.name) << " " << get_value(tmp.value) << endl;
                tmp.name = get_next(tmp.name);
                tmp.value = get_next(tmp.value);
            }
            continue;
        }
        if (add_var(a, name, val))
            cout << "OK\n";
        else {
            set_var (a, name, val);
        }
        out_to_file(a, "vars.txt");
    }
    out_by_namespace(a, "ord.txt");
    return 0;
}
